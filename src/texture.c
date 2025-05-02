/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:38:10 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/02 23:30:00 by vagarcia         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	allocate_texture_data(t_game *game)
{
	int	i;

	game->texture_data = (int **)malloc(sizeof(int *) * 4);
	if (!game->texture_data)
		error_exit(game, ERR_MEMORY);
	i = 0;
	while (i < 4)
	{
		game->texture_data[i] = (int *)malloc(sizeof(int) * 
				(TEX_WIDTH * TEX_HEIGHT));
		if (!game->texture_data[i])
			error_exit(game, ERR_MEMORY);
		i++;
	}
}

void	load_texture(t_game *game, int tex_num)
{
	int	x;
	int	y;
	int	pixel;
	double scale_x, scale_y;

	if (access(game->textures[tex_num].path, F_OK) != 0)
	{
		printf("Error: Texture file '%s' does not exist\n", game->textures[tex_num].path);
		error_exit(game, ERR_TEX_LOAD);
	}
	game->textures[tex_num].img.img = mlx_xpm_file_to_image(game->mlx,
			game->textures[tex_num].path, 
			&game->textures[tex_num].img.width,
			&game->textures[tex_num].img.height);
	if (!game->textures[tex_num].img.img)
	{
		printf("Error: Failed to load texture '%s'\n", game->textures[tex_num].path);
		error_exit(game, ERR_TEX_LOAD);
	}
	
	// Calculate scaling factors if the texture size doesn't match expected dimensions
	scale_x = (double)game->textures[tex_num].img.width / TEX_WIDTH;
	scale_y = (double)game->textures[tex_num].img.height / TEX_HEIGHT;
	if (scale_x != 1.0 || scale_y != 1.0)
	{
		printf("Info: Scaling texture '%s' from %dx%d to %dx%d\n", 
			game->textures[tex_num].path,
			game->textures[tex_num].img.width, game->textures[tex_num].img.height,
			TEX_WIDTH, TEX_HEIGHT);
	}
	
	game->textures[tex_num].img.addr = mlx_get_data_addr(
			game->textures[tex_num].img.img,
			&game->textures[tex_num].img.bits_per_pixel,
			&game->textures[tex_num].img.line_length,
			&game->textures[tex_num].img.endian);
	if (!game->textures[tex_num].img.addr)
		error_exit(game, ERR_MEMORY);
		
	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			// Use nearest neighbor scaling to sample from the source texture
			int src_x = (int)(x * scale_x);
			int src_y = (int)(y * scale_y);
			
			// Clamp source coordinates to valid range
			if (src_x >= game->textures[tex_num].img.width)
				src_x = game->textures[tex_num].img.width - 1;
			if (src_y >= game->textures[tex_num].img.height)
				src_y = game->textures[tex_num].img.height - 1;
				
			pixel = (src_y * game->textures[tex_num].img.line_length / 4 + src_x);
			game->texture_data[tex_num][y * TEX_WIDTH + x] = 
				((int *)game->textures[tex_num].img.addr)[pixel];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, game->textures[tex_num].img.img);
	game->textures[tex_num].img.img = NULL;
}

void	load_textures(t_game *game)
{
	int	i;

	allocate_texture_data(game);
	i = 0;
	while (i < 4)
	{
		load_texture(game, i);
		i++;
	}
}

void	free_textures(t_game *game)
{
	int	i;

	if (!game->texture_data)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->texture_data[i])
			free(game->texture_data[i]);
		i++;
	}
	free(game->texture_data);
	game->texture_data = NULL;
}

int	get_texture_color(t_game *game, int tex_num, int tex_x, int tex_y)
{
	if (tex_x < 0 || tex_x >= TEX_WIDTH || tex_y < 0 || tex_y >= TEX_HEIGHT
		|| tex_num < 0 || tex_num >= 4)
		return (0);
	return (game->texture_data[tex_num][TEX_WIDTH * tex_y + tex_x]);
}