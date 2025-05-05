/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:37:53 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/05 18:30:34 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// for debugging
/* void	printall(t_map *map)
{
	ft_printf("map is valid!\n\n");
	ft_printf("map->texture_NO = %s\n", map->texture_no);
	ft_printf("map->texture_SO = %s\n", map->texture_so);
	ft_printf("map->texture_WE = %s\n", map->texture_we);
	ft_printf("map->texture_EA = %s\n\n", map->texture_ea);
	ft_printf("F = %d, %d, %d\n", map->floor[0], map->floor[1], map->floor[2]);
	ft_printf("C = %d, %d, %d\n\n", map->ceiling[0], map->ceiling[1],
		map->ceiling[2]);
	print_array(map->grid);
	ft_printf("\nmap->height = %d\n", map->height);
	ft_printf("map->width = %d\n", map->width);
	ft_printf("--------------------------\n");
} */

void	free_textures_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].path)
			free(game->textures[i].path);
		i++;
	}
}

// Zero out the entire game struct to avoid uninitialized memory
// Use	printall(&game.map); for debug
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
		return (print_example("Error\nPlease only enter path of .cub\n"), 1);
	if (parse(&game.map, argv[1], 0))
		return (free_all(&game.map), 1);
	init_game(&game);
	if (game.mlx && game.win)
	{
		load_textures(&game);
		render_frame(&game);
		mlx_loop(game.mlx);
	}
	else
	{
		ft_dprintf(2, "Error\nFailed to initialize mlx or create window\n");
		exit_game(&game);
		return (1);
	}
	exit_game(&game);
	return (0);
}
