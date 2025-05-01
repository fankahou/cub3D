/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolt <bolt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by bolt              #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by bolt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.pos_x + game->player.dir_x * move_speed;
	new_y = game->player.pos_y + game->player.dir_y * move_speed;

	// Collision detection - only move if the new position is not a wall
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

	// Collision detection - only move if the new position is not a wall
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	// Strafe left - perpendicular to the direction vector
	new_x = game->player.pos_x - game->player.plane_x * move_speed;
	new_y = game->player.pos_y - game->player.plane_y * move_speed;

	// Collision detection - only move if the new position is not a wall
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	// Strafe right - perpendicular to the direction vector
	new_x = game->player.pos_x + game->player.plane_x * move_speed;
	new_y = game->player.pos_y + game->player.plane_y * move_speed;

	// Collision detection - only move if the new position is not a wall
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	// Rotate camera direction vector using a rotation matrix
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rot_speed) - 
		game->player.dir_y * sin(-rot_speed);
	game->player.dir_y = old_dir_x * sin(-rot_speed) + 
		game->player.dir_y * cos(-rot_speed);

	// Rotate camera plane vector using the same rotation matrix
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rot_speed) - 
		game->player.plane_y * sin(-rot_speed);
	game->player.plane_y = old_plane_x * sin(-rot_speed) + 
		game->player.plane_y * cos(-rot_speed);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	// Rotate camera direction vector using a rotation matrix
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed) - 
		game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + 
		game->player.dir_y * cos(rot_speed);

	// Rotate camera plane vector using the same rotation matrix
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed) - 
		game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + 
		game->player.plane_y * cos(rot_speed);
}

int	key_press(int keycode, t_game *game)
{
	// Debug information to see which key was pressed
	printf("Key pressed: %d\n", keycode);

	if (keycode == KEY_ESC)
		exit_game(game);
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
		rotate_left(game);
	else if (keycode == KEY_RIGHT)
		rotate_right(game);
	
	// Re-render the frame after movement
	render_frame(game);
	return (0);
}