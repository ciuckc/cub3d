/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:31:14 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/01/16 20:36:12 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"
#include <stdlib.h>

int32_t	main(int argc, char **argv)
{
	t_vars	vars;

	vars.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!vars.mlx)
		exit(EXIT_FAILURE);
	parse(argc, argv, &vars);
	vars.canvas = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(vars.mlx, vars.canvas, 0, 0);
	mlx_loop_hook(vars.mlx, &player_hook, &vars);
	mlx_loop_hook(vars.mlx, &render, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
