/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:38:06 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/06 13:57:02 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* void	draw_sth(t_game *game)
{
	int	y;
	int x;
	char	*dst;
	unsigned int	src;
	
	y = 0;
	while (y < 256)
	{	
		x = 0;
		while (x < 256)
		{
			dst = game->img.addr + (y * game->img.line_length + x
					* (game->img.bits_per_pixel / 8));
			src = game->texture_data[0][y * TEX_WIDTH + x];
			*(unsigned int *)dst = src;
			x++;
		}
		y++;
	}
} */

static int	check_map_size(t_game *game)
{
	int	pixel;
	int	max_height;
	int	max_width;

	pixel = 1;
	max_height = WIN_HEIGHT / MAP_SCALE;
	max_width = WIN_WIDTH / MAP_SCALE;
	while (pixel * game->map.height < max_height && pixel
		* game->map.width < max_width)
		pixel++;
	return (pixel);
}

void	draw_map(t_game *game, int x, int y, int pixel)
{
	char	*dst;

	pixel = check_map_size(game);
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			dst = game->img.addr + (y * game->img.line_length + x
					* (game->img.bits_per_pixel / 8));
			if (!game->map.grid[(y / pixel)])
				return ;
			if (!game->map.grid[(y / pixel)][(x / pixel)])
				break ;
			if (game->map.grid[(y / pixel)][(x / pixel)] == '1')
				*(unsigned int *)dst = 0;
			else
				*(unsigned int *)dst = create_rgb(255, 255, 255);
			if ((x / pixel) == (int)game->player.pos_x && (y
					/ pixel) == (int)game->player.pos_y)
				*(unsigned int *)dst = create_rgb(255, 0, 0);
			x++;
		}
		y++;
	}
}

void	draw_fps(t_game *game)
{
	struct timeval	time;

	game->frame++;
	gettimeofday(&time, NULL);
	if (game->second != time.tv_sec)
	{
		ft_printf("framerate == %d\n", game->frame);
		game->frame = 0;
		game->second = time.tv_sec;
	}
}

void	draw_bonus(t_game *game)
{
	draw_fps(game);
	draw_map(game, 0, 0, 0);
}
