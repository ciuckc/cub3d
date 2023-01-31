/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:31:14 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/01/31 16:06:05 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"
#include <stdlib.h>

int	mapindex(t_map *map, int x, int y)
{
	return (map->grid[x + y * map->size.x]);
}

int32_t	main(int argc, char **argv)
{
	t_vars	vars;

	vars.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!vars.mlx)
		exit(EXIT_FAILURE);
	parse(argc, argv, &vars);
	render2d_init(&vars);
	sprite_init(&vars, &vars.sprite[0], "assets/ghoulie2.xpm42");
	vars.canvas = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(vars.mlx, vars.canvas, 0, 0);
	vars.canvas->instances[0].z = Z_LVL_CANVAS;
	mlx_loop_hook(vars.mlx, &player_hook, &vars);
	mlx_loop_hook(vars.mlx, &render, &vars);
	mlx_loop_hook(vars.mlx, &render2d_minimap, &vars);
	mlx_loop_hook(vars.mlx, &enemy_hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
