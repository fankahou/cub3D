/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:38:22 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/02 23:38:15 by vagarcia         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"

// Constants for window dimensions
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define TEX_WIDTH 256
# define TEX_HEIGHT 256

// Error codes
# define ERR_MLX_INIT 1
# define ERR_MLX_WIN 2
# define ERR_TEX_LOAD 3
# define ERR_MEMORY 4

// Direction constants
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

// Linux key codes
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// Movement speed and rotation speed
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	t_img	img;
	char	*path;
}	t_texture;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	wall_x;
}	t_ray;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	color;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_img		img;
	t_texture	textures[4];
	t_color		floor;
	t_color		ceiling;
	int			**texture_data;
}	t_game;

// Raycasting functions
void	cast_rays(t_game *game);
void	init_ray(t_ray *ray, t_player *player, int x);
void	calculate_step_and_side_dist(t_ray *ray, t_player *player);
void	perform_dda(t_ray *ray, char **map, int map_height, int map_width);
void	calculate_wall_distance(t_ray *ray, t_player *player);
void	calculate_wall_height(t_ray *ray);
void	draw_vertical_line(t_game *game, t_ray *ray, int x);

// Texture functions
void	load_textures(t_game *game);
void	free_textures(t_game *game);
int		get_texture_color(t_game *game, int tex_num, int tex_x, int tex_y);
void	calculate_texture_x(t_ray *ray, t_player *player);
int		determine_texture(t_ray *ray);

// Utils
int		create_rgb(int r, int g, int b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		exit_game(t_game *game);
void	error_exit(t_game *game, int error_code);
void	init_game(t_game *game);
void	init_player_direction(t_game *game, char direction);
int		render_frame(t_game *game);
void	*ft_memset(void *b, int c, size_t len);

// Movement
int		key_press(int keycode, t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

#endif