/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2025/05/04 13:15:56 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// check if the X is next to a space, /n , /0, x == 0, y ==0
static void	check_x(t_map *map, int y, int x, char **temp)
{
	if (x == 0 || y == 0 || !temp[x + 1])
	{
		dprintf(2, "Error\nmap[%d][%d] is invalid\n", x, y);
		map->flag++;
	}
	else if (temp[x][y + 1] != '1' && temp[x][y + 1] != 'X')
	{
		dprintf(2, "Error\nmap[%d][%d] is invalid\n", x, y + 1);
		map->flag++;
	}
	else if (y > 0 && (temp[x][y - 1] != '1' && temp[x][y - 1] != 'X'))
	{
		dprintf(2, "Error\nmap[%d][%d] is invalid\n", x, y - 1);
		map->flag++;
	}
	else if (temp[x + 1] && (temp[x + 1][y] != '1' && temp[x + 1][y] != 'X'))
	{
		dprintf(2, "Error\nmap[%d][%d] is invalid\n", x + 1, y);
		map->flag++;
	}
	else if (x > 0 && (temp[x - 1][y] != '1' && temp[x - 1][y] != 'X'))
	{
		dprintf(2, "Error\nmap[%d][%d] is invalid\n", x - 1, y);
		map->flag++;
	}
}

// backtracking to and flood the map with X if the next square is 0
// will also put the starting point to X so it will throw error
// if there is more than 1 starting point
static void	find_route(t_map *map, int y, int x, char **temp)
{
	if (temp[x][y] == 'X')
		return ;
	temp[x][y] = 'X';
	if (map->map[x][y + 1] == '0')
		find_route(map, y + 1, x, temp);
	if (y > 0 && map->map[x][y - 1] == '0')
		find_route(map, y - 1, x, temp);
	if (map->map[x + 1] && map->map[x + 1][y] == '0')
		find_route(map, y, x + 1, temp);
	if (x > 0 && map->map[x - 1][y] == '0')
		find_route(map, y, x - 1, temp);
	check_x(map, y, x, temp);
}

static int	fill_map(t_map *map, int y, int x)
{
	char	**temp;

	temp = copy_map(map->map);
	if (!temp)
		return (1);
	find_route(map, y, x, temp);
	if (map->flag != 0)
	{
		write(2, "please check map:\n", 18);
		print_array(temp);
		ft_free_split(temp);
		return (1);
	}
	ft_free_split(temp);
	return (0);
}

// check gnl error and if map is enclosed
int	check_map(t_map *map, int gnl_flag, int line)
{
	int	x;
	int	y;

	(void)line;
	if (gnl_flag == 1)
		return (ft_dprintf(2, "Error\ngnl failed\n"), 1);
	x = 0;
	while (map->map[x])
	{
		y = 0;
		while (map->map[x][y] && map->map[x][y] != '\n')
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'S'
				|| map->map[x][y] == 'E' || map->map[x][y] == 'W')
			{
				if (fill_map(map, y, x))
					return (1);
				map->flag--;
			}
			y++;
		}
		x++;
	}
	return (0);
}
