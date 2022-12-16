/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:31:14 by mbatstra          #+#    #+#             */
/*   Updated: 2022/12/16 19:13:59 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

int32_t	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		return (EXIT_FAILURE);
	parse(argv, &vars.map);
	vars.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!vars.mlx)
		exit(EXIT_FAILURE);
	vars.canvas = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	// render2d(vars.mlx, &vars.map);
	mlx_image_to_window(vars.mlx, vars.canvas, 0, 0);
	player_init(&vars);
	mlx_loop_hook(vars.mlx, &player_hook, &vars);
	// mlx_loop_hook(vars.mlx, &player_routine, &vars);
	mlx_loop_hook(vars.mlx, &render, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
