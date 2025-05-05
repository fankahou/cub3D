/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:38:06 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/05 17:51:55 by kfan             ###   ########.fr       */
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
	if (game->move[0] == 1)
		move_forward(game);
	else if (game->move[1] == 1)
		move_backward(game);
	if (game->move[2] == 1)
		move_left(game);
	else if (game->move[3] == 1)
		move_right(game);
	if (game->move[4] == 1)
		rotate_left(game);
	else if (game->move[5] == 1)
		rotate_right(game);
}

// later we can print framerate on the screen for debugging?
int	render_frame(t_game *game)
{
	struct timeval	time;

	update_move(game);
	game->frame++;
	gettimeofday(&time, NULL);
	if (game->second != time.tv_sec)
	{
		ft_printf("framerate == %d\n", game->frame);
		game->frame = 0;
		game->second = time.tv_sec;
	}
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
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = NULL;
	return (0);
}
