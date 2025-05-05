/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:37:58 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/05 17:26:17 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Rotate camera direction vector using a rotation matrix
// Rotate camera plane vector using the same rotation matrix
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rot_speed)
		- game->player.dir_y * sin(-rot_speed);
	game->player.dir_y = old_dir_x * sin(-rot_speed) + game->player.dir_y
		* cos(-rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rot_speed)
		- game->player.plane_y * sin(-rot_speed);
	game->player.plane_y = old_plane_x * sin(-rot_speed) + game->player.plane_y
		* cos(-rot_speed);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
		* cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y
		* cos(rot_speed);
}

// Debug information to see which key was pressed
//printf("Key pressed: %d\n", keycode)
// Dont Re-render the frame after movement
// render_frame(game); < it will slow down the game
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	else if (keycode == KEY_W)
		game->move[0] = 1;
	else if (keycode == KEY_S)
		game->move[1] = 1;
	else if (keycode == KEY_A)
		game->move[2] = 1;
	else if (keycode == KEY_D)
		game->move[3] = 1;
	else if (keycode == KEY_LEFT)
		game->move[4] = 1;
	else if (keycode == KEY_RIGHT)
		game->move[5] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->move[0] = 0;
	else if (keycode == KEY_S)
		game->move[1] = 0;
	else if (keycode == KEY_A)
		game->move[2] = 0;
	else if (keycode == KEY_D)
		game->move[3] = 0;
	else if (keycode == KEY_LEFT)
		game->move[4] = 0;
	else if (keycode == KEY_RIGHT)
		game->move[5] = 0;
	return (0);
}
