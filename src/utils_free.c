/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2025/05/04 16:33:56 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	free_all(t_map *map)
{
	if (map->texture_no)
		free(map->texture_no);
	if (map->texture_so)
		free(map->texture_so);
	if (map->texture_we)
		free(map->texture_we);
	if (map->texture_ea)
		free(map->texture_ea);
	ft_free_split(map->grid);
}

void	free_parse(int fd, char *temp)
{
	int	gnl_flag;

	gnl_flag = 0;
	if (temp)
		free(temp);
	close(fd);
	get_next_line(-1, &gnl_flag);
}
