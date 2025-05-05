/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:38:01 by vagarcia          #+#    #+#             */
/*   Updated: 2025/05/05 18:11:14 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}
/* 
I just want to comment this out so I can check it later without norming it
void	perform_dda(t_ray *ray, char **map, int map_height, int map_width)
{
	int	steps;

	int max_distance = 100; // Set a reasonable maximum distance for rays
	steps = 0;
	
	while (ray->hit == 0 && steps < max_distance)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
			}
		
		// Check if ray is outside map bounds
		if (ray->map_x < 0 || ray->map_x >= map_width || 
			ray->map_y < 0 || ray->map_y >= map_height)
		{
			ray->hit = 1; // Consider it a hit to stop the loop
			continue ; // Skip the rest of this iteration
		}
		
		// Make sure the map row exists and the column is in bounds
		if (map[ray->map_y] != NULL
			&& ray->map_x < (int)ft_strlen(map[ray->map_y]))
		{
			if (map[ray->map_y][ray->map_x] == '1')
				ray->hit = 1;
		}
		else
		{
			ray->hit = 1; // Consider it a hit to stop the loop
		}
		
		steps++;
	}
	
	// If we hit the max distance, ensure we don't try to access invalid memory
	if (steps >= max_distance)
		ray->hit = 1;
} */

static int	perform_dda1(t_ray *ray, int map_height, int map_width)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
	if (ray->map_x < 0 || ray->map_x >= map_width || ray->map_y < 0
		|| ray->map_y >= map_height)
	{
		ray->hit = 1;
		return (1);
	}
	return (0);
}

void	perform_dda(t_ray *ray, char **map, int map_height, int map_width)
{
	int	max_distance;
	int	steps;

	max_distance = 100;
	steps = 0;
	while (ray->hit == 0 && steps < max_distance)
	{
		if (perform_dda1(ray, map_height, map_width))
			continue ;
		if (map[ray->map_y] != NULL
			&& ray->map_x < (int)ft_strlen(map[ray->map_y]))
		{
			if (map[ray->map_y][ray->map_x] == '1')
				ray->hit = 1;
		}
		else
			ray->hit = 1;
		steps++;
	}
	if (steps >= max_distance)
		ray->hit = 1;
}

int	determine_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

void	cast_rays(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, &game->player, x);
		calculate_step_and_side_dist(&ray, &game->player);
		perform_dda(&ray, game->map.grid, game->map.height, game->map.width);
		calculate_wall_distance(&ray, &game->player);
		calculate_wall_height(&ray);
		calculate_texture_x(&ray, &game->player);
		draw_vertical_line(game, &ray, x);
		x++;
	}
}
