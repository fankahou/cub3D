/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolt <bolt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by bolt              #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by bolt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../Libft/libft.h"

size_t    ft_strlen(const char *s)
{
    size_t	i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}


char	*ft_strdup(const char *s)
{
    char    *str;
    int     i;

    i = 0;
    str = malloc(ft_strlen(s) + 1);
    if (!str)
        return (NULL);
    while (s[i])
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}

void	init_test_map(t_game *game)
{
    int i;

    // Initialize the grid pointer to NULL first
    game->map.grid = NULL;
    
	game->map.width = 10;
	game->map.height = 10;
	game->map.grid = (char **)malloc(sizeof(char *) * game->map.height);
	if (!game->map.grid)
		error_exit(game, ERR_MEMORY);
    
    i = 0;
    while (i < game->map.height)
    {
        game->map.grid[i] = NULL;
        i++;
    }

	char *test_map[] = {
		"1111111111",
		"1000000001",
		"1010001001",
		"1000000001",
		"1000N00001",
		"1001000001",
		"1000000001",
		"1000000101",
		"1000000001",
		"1111111111"
	};
    
    i = 0;
    while (i < game->map.height)
	{
		game->map.grid[i] = ft_strdup(test_map[i]);
		if (!game->map.grid[i])
			error_exit(game, ERR_MEMORY);
        i++;
	}
}

void	init_test_textures(t_game *game)
{
	game->textures[NORTH].path = ft_strdup("./textures/north.xpm");
	game->textures[SOUTH].path = ft_strdup("./textures/south.xpm");
	game->textures[EAST].path = ft_strdup("./textures/east.xpm");
	game->textures[WEST].path = ft_strdup("./textures/west.xpm");
	
	if (!game->textures[NORTH].path || !game->textures[SOUTH].path || 
		!game->textures[EAST].path || !game->textures[WEST].path)
		error_exit(game, ERR_MEMORY);

	game->floor.r = 100;
	game->floor.g = 100;
	game->floor.b = 100;

	game->ceiling.r = 135;
	game->ceiling.g = 206;
	game->ceiling.b = 235;
}

void	find_player_pos(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
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

	if (argc < 2)
	{
		printf("Error: Missing map file argument\n");
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}

	// Zero out the entire game struct to avoid uninitialized memory
	ft_memset(&game, 0, sizeof(t_game));
	
	// For testing the raycasting im using a hardcoded map lol
    // After implementing parsing we can just call init_map(&game, argv[1]);
	init_test_map(&game);
	init_test_textures(&game);
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
