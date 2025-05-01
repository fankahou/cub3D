/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2025/05/01 19:09:36 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		i++;
	while (i >= 0)
	{
		if (array[i])
			free(array[i]);
		array[i] = NULL;
		i--;
	}
	if (array)
		free(array);
	array = NULL;
}

void free_all(t_map	*map)
{
	if (map->texture_NO)
		free(map->texture_NO);
	if (map->texture_SO)
		free(map->texture_SO);
	if (map->texture_WE)
		free(map->texture_WE);
	if (map->texture_EA)
		free(map->texture_EA);
	ft_free_split(map->map);
}

void free_parse(int fd, char *temp)
{
	int gnl_flag;
	
	gnl_flag = 0;
	if (temp)
		free(temp);
	close(fd);
	get_next_line(-1, &gnl_flag);
}