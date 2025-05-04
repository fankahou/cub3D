/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2025/05/04 16:24:22 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// change i < 5 to not take ".cub"
int	init_map(t_map *map, char *input)
{
	int	i;

	map->texture_no = NULL;
	map->texture_so = NULL;
	map->texture_we = NULL;
	map->texture_ea = NULL;
	map->grid = NULL;
	map->flag = 0;
	i = 0;
	while (i < 7)
	{
		map->identifier[i] = 0;
		i++;
	}
	i = 0;
	while (input[i])
		i++;
	if (i < 4 || ft_strncmp(&input[i - 4], ".cub", 4))
		return (identifier_error(-1, 0), 1);
	return (0);
}

// translation from Ka Hou's parsing to Valentino's game
void	init_bridge(t_game *game)
{
	game->textures[NORTH].path = game->map.texture_no;
	game->textures[SOUTH].path = game->map.texture_so;
	game->textures[EAST].path = game->map.texture_we;
	game->textures[WEST].path = game->map.texture_ea;
	game->floor.r = game->map.floor[0];
	game->floor.g = game->map.floor[1];
	game->floor.b = game->map.floor[2];
	game->ceiling.r = game->map.ceiling[0];
	game->ceiling.g = game->map.ceiling[1];
	game->ceiling.b = game->map.ceiling[2];
}
