/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2025/05/01 19:09:27 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_if_failed(char **temp, int i)
{
	while (i > 0)
		free(temp[--i]);
	free(temp);
}

char	**add_array(char **input, char *entry, int y)
{
	char	**temp;
	int		i;

	while (input && input[y])
		y++;
	temp = malloc(sizeof(char *) * (y + 2));
	if (!temp)
		return (perror("add_array: malloc failed"), NULL);
	temp[y + 1] = NULL;
	i = 0;
	while (i < y)
	{
		temp[i] = ft_strdup(input[i]);
		if (!temp[i])
			return (free_if_failed(temp, i), perror("add_array: ft_strdup failed"), NULL);
		i++;
	}
	temp[y] = ft_strdup(entry);
	if (!temp[y])
		return (free_if_failed(temp, i), perror("add_array: ft_strdup failed"), NULL);
	return (temp);
}
