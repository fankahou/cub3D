/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:38:06 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/06 13:54:39 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

// to make game smoother
// instead of in keycode event
// can move and turn at the same time
void	update_move(t_game *game)
{
	if (game->move[W] == 1)
		move_forward(game);
	else if (game->move[S] == 1)
		move_backward(game);
	if (game->move[A] == 1)
		move_left(game);
	else if (game->move[D] == 1)
		move_right(game);
	if (game->move[LEFT] == 1)
		rotate_left(game);
	else if (game->move[RIGHT] == 1)
		rotate_right(game);
}

// later we can print framerate on the screen for debugging?
int	render_frame(t_game *game)
{
	update_move(game);
	if (game->win == NULL)
		return (1);
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
		error_exit(game, ERR_MEMORY);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		error_exit(game, ERR_MEMORY);
	cast_rays(game);
	draw_bonus(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = NULL;
	return (0);
}
