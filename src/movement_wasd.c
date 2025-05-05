/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_wasd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:37:58 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/05 17:23:33 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// below: Collision detection - only move if the new position is not a wall
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.pos_x + game->player.dir_x * move_speed;
	new_y = game->player.pos_y + game->player.dir_y * move_speed;
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.pos_x - game->player.dir_x * move_speed;
	new_y = game->player.pos_y - game->player.dir_y * move_speed;
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

// Strafe left - perpendicular to the direction vector
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.pos_x - game->player.plane_x * move_speed;
	new_y = game->player.pos_y - game->player.plane_y * move_speed;
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

// Strafe right - perpendicular to the direction vector
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.pos_x + game->player.plane_x * move_speed;
	new_y = game->player.pos_y + game->player.plane_y * move_speed;
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}
