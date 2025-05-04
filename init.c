/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2025/05/04 13:13:42 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// change i < 5 to not take ".cub"
int	init_map(t_map *map, char *input)
{
	int	i;

	map->texture_NO = NULL;
	map->texture_SO = NULL;
	map->texture_WE = NULL;
	map->texture_EA = NULL;
	map->map = NULL;
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
