/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:38:14 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/04 15:12:21 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_exit(t_game *game, int error_code)
{
	if (error_code == ERR_MLX_INIT)
		printf("Error\nFailed to initialize MLX\n");
	else if (error_code == ERR_MLX_WIN)
		printf("Error\nFailed to create MLX window\n");
	else if (error_code == ERR_TEX_LOAD)
		printf("Error\nFailed to load texture\n");
	else if (error_code == ERR_MEMORY)
		printf("Error\nMemory allocation failed\n");
	else
		printf("Error\nUnknown error\n");
	exit_game(game);
	exit(EXIT_FAILURE);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height && map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

// Helper function to free texture paths
void	free_texture_paths(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].path)
			free(game->textures[i].path);
		game->textures[i].path = NULL;
		i++;
	}
}

int	exit_game(t_game *game)
{
	if (!game)
		exit(EXIT_SUCCESS);
	free_texture_paths(game);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	free_textures(game);
	free_map(&game->map);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		// In Linux with minilibx-linux, we need to call mlx_destroy_display to clean up X11 resources
		#ifdef __linux__
			mlx_destroy_display(game->mlx);
		#endif
		free(game->mlx);
		game->mlx = NULL;
	}
	exit(EXIT_SUCCESS);
	return (0);
}

void	init_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

// Loop hook to handle the frame rendering
int	loop_hook(t_game *game)
{
	render_frame(game);
	return (0);
}

// Example of how to initialize the game structure
// This would be called from your main.c
void	init_game(t_game *game)
{

    game->win = NULL;
    game->mlx = NULL;
    game->mlx = mlx_init();
	if (!game->mlx)
		error_exit(game, ERR_MLX_INIT);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		error_exit(game, ERR_MLX_WIN);
	game->img.img = NULL;
	game->texture_data = NULL;
	game->floor.color = create_rgb(game->floor.r, game->floor.g, game->floor.b);
	game->ceiling.color = create_rgb(game->ceiling.r, 
			game->ceiling.g, game->ceiling.b);
	
	// Set up event hooks for proper X11 resource management
	mlx_hook(game->win, 2, 1L << 0, key_press, game);        // KeyPress event
	mlx_hook(game->win, 17, 0, exit_game, game);            // Window close event
	mlx_loop_hook(game->mlx, loop_hook, game);              // Regular frame updates
}