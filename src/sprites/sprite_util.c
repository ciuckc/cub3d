/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:05:34 by mbatstra          #+#    #+#             */
/*   Updated: 2023/02/15 16:20:28 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42.h"
#include "parse.h"
#include "libft.h"
#include "cub3d.h"

// load the xpm into an mlx image and set the sprite position
void	st_init_sprite(t_vars *vars, t_sprite *sprt, char *path, t_vect2 i)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42(path);
	if (xpm == NULL)
		exit_strerr(MALLOC_ERR);
	sprt->tex = mlx_texture_to_image(vars->mlx, &xpm->texture);
	if (sprt->tex == NULL)
		exit_strerr(MALLOC_ERR);
	sprt->pos.x = (double)(i.x + 0.5);
	sprt->pos.y = (double)(i.y + 0.5);
}

// count all sprites in the map
uint32_t	st_count_sprites(t_vars *vars)
{
	uint32_t	num_sprites;
	t_vect2		i;
	t_map		*map;

	num_sprites = 0;
	map = &vars->map;
	i.y = 0;
	while (i.y < map->size.y)
	{
		i.x = 0;
		while (i.x < map->size.x)
		{
			if (mapindex(map, i.x, i.y) == ENEMY || \
				mapindex(map, i.x, i.y) == EXIT || \
				mapindex(map, i.x, i.y) == COLLEC)
				num_sprites++;
			i.x++;
		}
		i.y++;
	}
	return (num_sprites);
}

// based on the type of the sprite this function inits the right texture
// and also sets the enemy flag (is it an enemy or an exit/collectible)
void	st_set_sprite_type(t_vars *vars, t_vect2 i, uint32_t *i_spr)
{
	if (mapindex(&vars->map, i.x, i.y) == ENEMY)
	{
		if ((i.x + i.y) % 2)
			st_init_sprite(vars, &vars->sprite[*i_spr], ENEMY1_PATH, i);
		else
			st_init_sprite(vars, &vars->sprite[*i_spr], ENEMY2_PATH, i);
		vars->sprite[*i_spr].is_enemy = true;
		*i_spr += 1;
	}
	else if (mapindex(&vars->map, i.x, i.y) == COLLEC)
	{
		st_init_sprite(vars, &vars->sprite[*i_spr], COLLEC_PATH, i);
		vars->sprite[*i_spr].is_enemy = false;
		*i_spr += 1;
	}
	else if (mapindex(&vars->map, i.x, i.y) == EXIT)
	{
		st_init_sprite(vars, &vars->sprite[*i_spr], EXIT_PATH, i);
		vars->sprite[*i_spr].is_enemy = false;
		*i_spr += 1;
	}
}

// driver code for above functions
// allocates memory for all sprites, both enemies and collecs/exit
// iterates over map setting eacht texture and enemy flag when encoutering
// a sprite of some sort
void	sprites_init(t_vars *vars)
{
	t_sprite	*sprites;
	uint32_t	arr_size;
	uint32_t	i_spr;
	t_vect2		i;

	arr_size = st_count_sprites(vars);
	vars->num_sprites = arr_size;
	sprites = (t_sprite *)malloc(arr_size * sizeof(t_sprite));
	if (sprites == NULL)
		exit_strerr(MALLOC_ERR);
	vars->sprite = sprites;
	i.y = 0;
	i_spr = 0;
	while (i.y < vars->map.size.y)
	{
		i.x = 0;
		while (i.x < vars->map.size.x)
		{
			st_set_sprite_type(vars, i, &i_spr);
			i.x++;
		}
		i.y++;
	}
}

// wrapper that doesn't put black pixels
// might be nice to change sprites so that they use that one classic
// purple as invisible color instead
void	sprite_put_pixel(t_vars *vars, t_vect2 i, t_vect2 img_i, t_sprite *spr)
{
	if (get_pixel(spr->tex, img_i) & 0xffffff00)
		mlx_put_pixel(vars->canvas, i.x, i.y, get_pixel(spr->tex, img_i));
}
