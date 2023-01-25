/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:17:50 by mbatstra          #+#    #+#             */
/*   Updated: 2023/01/25 19:48:19 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "parse.h"
#include "libft.h"
#include "cub3d.h"

void	init_hud(t_vars *vars)
{
	mlx_image_t	*hud_img;
	mlx_t		*mlx;
	xpm_t		*xpm;

	if (WIDTH != 1024 || HEIGHT != 1024)
		return ;
	mlx = vars->mlx;
	xpm = mlx_load_xpm42(HUD_PATH);
	if (xpm == NULL)
		exit_strerr(IMG_ERR);
	hud_img = mlx_texture_to_image(mlx, &xpm->texture);
	if (hud_img == NULL)
		exit_strerr(IMG_ERR);
	vars->texture2d[0] = hud_img;
	mlx_image_to_window(vars->mlx, vars->texture2d[0], 0, 0);
	vars->texture2d[0]->instances[0].z = Z_LVL_HUD;
}

void	init_player2d(t_vars *vars)
{
	mlx_image_t	*img;
	uint32_t	tilesize;
	uint32_t	mapsize;

	if (WIDTH >= HEIGHT)
		mapsize = WIDTH * MAPSCALE;
	else
		mapsize = HEIGHT * MAPSCALE;
	tilesize = mapsize / TPM;
	img = mlx_new_image(vars->mlx, tilesize / 8, tilesize / 8);
	ft_memset(img->pixels, PLAYER2D_CLR, \
				img->width * img->height * sizeof(int32_t));
	vars->texture2d[2] = img;
	mlx_image_to_window(vars->mlx, img, \
					mapsize / 2 - tilesize / 16, mapsize / 2 - tilesize / 16);
	vars->texture2d[2]->instances[0].z = Z_LVL_HUD;
}

void	init_minimap(t_vars *vars)
{
	uint32_t	mapsize;

	if (WIDTH >= HEIGHT)
		mapsize = WIDTH * MAPSCALE;
	else
		mapsize = HEIGHT * MAPSCALE;
	mapsize += mapsize / TPM;
	vars->texture2d[1] = mlx_new_image(vars->mlx, mapsize, mapsize);
	mlx_image_to_window(vars->mlx, vars->texture2d[1], 0, 0);
	vars->texture2d[1]->instances[0].z = Z_LVL_MINIMAP;
	render2d_minimap(vars);
}

void	render2d_init(t_vars *vars)
{
	init_minimap(vars);
	init_player2d(vars);
	init_hud(vars);
}
