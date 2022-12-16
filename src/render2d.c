/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:21:43 by mbatstra          #+#    #+#             */
/*   Updated: 2022/12/14 16:06:02 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"

int	mapindex(t_map *map, int x, int y)
{
	return (map->grid[x + y * map->size.x]);
}

void	fill_img(mlx_image_t *img, uint32_t clr)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (x < img->width)
	{
		while (y < img->height)
		{
			if (x == 0 || x == img->width - 1 || y == 0 || y == img->height - 1)
				mlx_put_pixel(img, x, y, 0xffffffff);
			else
				mlx_put_pixel(img, x, y, clr);
			y++;
		}
		y = 0;
		x++;
	}
}

void	render2d(mlx_t *mlx, t_map *map)
{
	mlx_image_t	*wall_img;
	mlx_image_t	*floor_img;
	int			x;
	int			y;

	x = 0;
	y = 0;
	wall_img = mlx_new_image(mlx, TILESIZE, TILESIZE);
	floor_img = mlx_new_image(mlx, TILESIZE, TILESIZE);
	fill_img(wall_img, 0xdbb856ff);
	fill_img(floor_img, 0x81b5b2ff);
	while (y < map->size.y)
	{
		while (x < map->size.x)
		{
			if (mapindex(map, x, y) == WALL)
				mlx_image_to_window(mlx, wall_img, x * TILESIZE, y * TILESIZE);
			else
				mlx_image_to_window(mlx, floor_img, x * TILESIZE, y * TILESIZE);
			x++;
		}
		x = 0;
		y++;
	}
}
