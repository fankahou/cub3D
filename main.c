/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2025/05/04 13:14:30 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// for debugging
void	printall(t_map *map)
{
	ft_printf("map is valid!\n\n");
	ft_printf("map->texture_NO = %s\n", map->texture_NO);
	ft_printf("map->texture_SO = %s\n", map->texture_SO);
	ft_printf("map->texture_WE = %s\n", map->texture_WE);
	ft_printf("map->texture_EA = %s\n\n", map->texture_EA);
	ft_printf("F = %d, %d, %d\n", map->floor[0], map->floor[1], map->floor[2]);
	ft_printf("C = %d, %d, %d\n\n", map->ceiling[0], map->ceiling[1],
		map->ceiling[2]);
	print_array(map->map);
	ft_printf("--------------------------\n");
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (print_example("Error\nPlease enter one argument\n"), 26);
	if (parse(&map, argv[1], 0))
		return (free_all(&map), 1);
	printall(&map); // for debugging
	// do sth;
	free_all(&map);
	return (0);
}
