/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:37:53 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/04 16:50:17 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// for debugging
void	printall(t_map *map)
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
}

// note for Valentino:
// I added another check in the loop to avoid invalid read
// as some of the lines could be shorter:
// while (game->map.grid[y][x] && x < game->map.width)
void	find_player_pos(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x] && x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				init_player_direction(game, c);
				game->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void free_textures_paths(t_game *game)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].path)
			free(game->textures[i].path);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	// Zero out the entire game struct to avoid uninitialized memory
	ft_memset(&game, 0, sizeof(t_game));
	
	if (argc != 2)
		return (print_example("Error\nPlease enter one argument as the path of <map.cub>\n"), 26);
	if (parse(&game.map, argv[1], 0))
		return (free_all(&game.map), 1);
	printall(&game.map); // for debugging
	init_bridge(&game);//transfer textures and colours from map to game
	find_player_pos(&game);
	init_game(&game);
	
	if (game.mlx && game.win)
	{
		load_textures(&game);
		render_frame(&game);
		mlx_loop(game.mlx);
	}
    else
    {
        printf("Error: Failed to initialize mlx or create window\n");
        exit_game(&game);
        return (1);
    }
	exit_game(&game);
	return (0);
}
