/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:38:10 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/22 16:05:27 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_game *game)
{
	int	i;

	if (!game->texture_data)
		return ;
	i = 0;
	while (game->texture_data && i < 4)
	{
		if (game->texture_data[i])
			free(game->texture_data[i]);
		i++;
	}
	free(game->texture_data);
	game->texture_data = NULL;
}

int	get_texture_color(t_game *game, int tex_num, int tex_x, int tex_y)
{
	if (tex_x < 0 || tex_x >= TEX_WIDTH || tex_y < 0 || tex_y >= TEX_HEIGHT
		|| tex_num < 0 || tex_num >= 4)
		return (0);
	return (game->texture_data[tex_num][TEX_WIDTH * tex_y + tex_x]);
}
