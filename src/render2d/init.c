/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:17:50 by mbatstra          #+#    #+#             */
/*   Updated: 2023/03/13 15:41:07 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "parse.h"
#include "libft.h"
#include "cub3d.h"

// load HUD texture and dispaly it
// until we make a proper scaling algorithm, this only executes
// when WIDTH and HEIGHT are 1024
void	st_init_hud(t_vars *vars)
{
	mlx_texture_t	*tex;
	mlx_image_t		*hud_img;
	mlx_t			*mlx;

	mlx = vars->mlx;
	tex = mlx_load_png(HUD_PATH);
	if (tex == NULL)
		exit_strerr(IMG_ERR);
	hud_img = mlx_texture_to_image(mlx, tex);
	if (hud_img == NULL)
		exit_strerr(IMG_ERR);
	mlx_delete_texture(tex);
	vars->texture2d[0] = hud_img;
	mlx_image_to_window(vars->mlx, vars->texture2d[0], 0, 0);
	mlx_set_instance_depth(&vars->texture2d[0]->instances[0], Z_LVL_HUD);
}

// display the cube at the center of the minimap
void	st_init_player2d(t_vars *vars)
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
	mlx_set_instance_depth(&vars->texture2d[2]->instances[0], Z_LVL_MAPDOT);
}

// create the image for the minimap and then call the rendering func
// to fill it up
void	st_init_minimap(t_vars *vars)
{
	uint32_t	mapsize;

	if (WIDTH >= HEIGHT)
		mapsize = WIDTH * MAPSCALE;
	else
		mapsize = HEIGHT * MAPSCALE;
	mapsize += mapsize / TPM;
	vars->texture2d[1] = mlx_new_image(vars->mlx, mapsize, mapsize);
	mlx_image_to_window(vars->mlx, vars->texture2d[1], 0, 0);
	render2d_minimap(vars);
	mlx_set_instance_depth(&vars->texture2d[1]->instances[0], Z_LVL_MINIMAP);
}

void	st_init_sky(t_vars *vars)
{	
	mlx_image_t	*sky_img1;
	mlx_image_t	*sky_img2;
	mlx_t		*mlx;
	xpm_t		*xpm;

	mlx = vars->mlx;
	xpm = mlx_load_xpm42(SKY_PATH);
	if (xpm == NULL)
		exit_strerr(IMG_ERR);
	sky_img1 = mlx_texture_to_image(mlx, &xpm->texture);
	if (sky_img1 == NULL)
		exit_strerr(IMG_ERR);
	vars->texture2d[3] = sky_img1;
	sky_img2 = mlx_texture_to_image(mlx, &xpm->texture);
	if (sky_img2 == NULL)
		exit_strerr(IMG_ERR);
	mlx_delete_xpm42(xpm);
	vars->texture2d[4] = sky_img2;
	mlx_image_to_window(vars->mlx, vars->texture2d[3], 0, 0);
	mlx_image_to_window(vars->mlx, vars->texture2d[4], WIDTH, 0);
	mlx_set_instance_depth(&vars->texture2d[3]->instances[0], Z_LVL_BACKGRND);
	mlx_set_instance_depth(&vars->texture2d[4]->instances[0], Z_LVL_BACKGRND);
}

// driver code for above static funcs
void	render2d_init(t_vars *vars)
{
	st_init_minimap(vars);
	st_init_player2d(vars);
	init_interact(vars);
	if (WIDTH == 1024 && HEIGHT == 1024)
		st_init_hud(vars);
	st_init_sky(vars);
}
