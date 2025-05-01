/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2025/05/01 19:19:41 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parse_path(t_map *map, char *path, int x)
{
	char *temp;
	// check path? check dir? dont know what they are yet...
/* 	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return(perror("Open failed"), 1); */
	temp = ft_strtrim(path, "\n");
	if (!temp)
		return(perror("ft_strtrim failed"), 1);
	if (x == 0)
		map->texture_NO = temp;
	if (x == 1)
		map->texture_SO = temp;
	if (x == 2)
		map->texture_WE = temp;
	if (x == 3)
		map->texture_EA = temp;
	return (0);
}

static int parse_colour_range(t_map *map, char *rgb, int x)
{
	char **temp;
	int	i;
	int colour;

	temp = ft_split(rgb, ',');
	if (!temp)
		return(perror("ft_split failed"), 1);
	i = 0;
	while (i < 3 && temp[i])
	{
		colour = ft_atoi(temp[i]);
		if (colour < 0 || colour > 255)// check also overflow?
			return (colour_error(i, x, temp), 1);
		if (x == 5)
			map->floor[i] = colour;
		else
			map->ceiling[i] = colour;
		i++;
	}
	if (i != 3)
		return (colour_error(3, x, temp), 1);
	ft_free_split(temp);
	return (0);
}

static int	parse_line(t_map *map, char *temp, int x)
{
	if (x == 0 && !ft_strncmp("NO ./", temp, 5))
		return(parse_path(map, &temp[5], x));
	else if (x == 0)
		return (identifier_error(x), 1);
	if (x == 1 && !ft_strncmp("SO ./", temp, 5))
		return(parse_path(map, &temp[5], x));
	else if (x == 1)
		return (identifier_error(x), 1);
	if (x == 2 && !ft_strncmp("WE ./", temp, 5))
		return(parse_path(map, &temp[5], x));
	else if (x == 2)
		return (identifier_error(x), 1);
	if (x == 3 && !ft_strncmp("EA ./", temp, 5))
		return(parse_path(map, &temp[5], x));
	else if (x == 3)
		return (identifier_error(x), 1);
	if ((x == 5 && !ft_strncmp("F ", temp, 2)) || (x == 6 && !ft_strncmp("C ", temp, 2)))
		return (parse_colour_range(map, &temp[2], x));
	else if (x == 5 || x == 6)
		return (identifier_error(x), 1);
	if ((x == 4 || x == 7)&& ft_strncmp("\n", temp, 1))
		return (identifier_error(x), 1);
	return (0);
}

static int	parse_map(t_map *map, char *temp, int x, int y)
{
	char **array;
	char *new;

	new = ft_strtrim(temp, "\n");
	if (!new)
		return(perror("ft_strtrim failed"), 1);
	while(new[y])
	{
		if (new[y] != '0' && new[y] != '1' && new[y] != ' ' && new[y] != 'N' && new[y] != 'S' && new[y] != 'E' && new[y] != 'W')
		{
			write(2, "line ", 5);
			ft_putnbr_fd(x + 1, 2);
			write(2, ": invalid character \"", 21);
			write(2, &new[y], 1);
			write(2, "\"\n", 2);
			return (free(new), 1);
		}
		y++;
	}
	array = add_array(map->map, new, 0);
	if (!array)
		return(free(new), 1);
	ft_free_split(map->map);
	map->map = array;
	return (free(new), 0);
}

int	parse(t_map	*map, char *input, int x)
{
	int		fd;
	char	*temp;
	int		gnl_flag;
	
	gnl_flag = 0;
	init_map(map);
	fd = open(input, O_RDONLY);
	if (fd < 0)
		return(perror("Open failed"), 1);
	while (1)
	{
		temp = get_next_line(fd, &gnl_flag);
		if (!temp)
			break ;
		if (x < 8 && parse_line(map, temp, x))
			return (free_parse(fd, temp), 1);
		else if (x > 7 && parse_map(map, temp, x, 0))
			return (free_parse(fd, temp), 1);
		free(temp);
		x++;
	}
	free_parse(fd, NULL);
/* 	if (check_map(map, gnl_flag, x));
		return (1); */
	return (0);
}
