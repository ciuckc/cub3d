/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:37:30 by mbatstra          #+#    #+#             */
/*   Updated: 2023/03/17 16:48:16 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

// window dimensions
// a lot off the bonus stuff will look bad in any other size than
// 1024 x 1024 and can only be turned off manually
# define WIDTH 1024
# define HEIGHT 1024

// minimap settings
// scale refers to minimap size proportional to the window
// tpm is tiles per map, eg the tilesize in the minimap
# define MAPSCALE 0.275
# define TPM 8

// number of seconds it takes to go to a new frame for animated sprites
// this is shared for all sprites
# define ANIM_FR 0.15

// player movement settings
# define MOV_SPD 0.1
# define ROT_SPD 0.1
# define ENEMY_SPD 0.025
# define FOV 1.0471976 // pi / 3

#endif
