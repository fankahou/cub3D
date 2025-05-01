/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:00:37 by kfan              #+#    #+#             */
/*   Updated: 2025/05/01 19:18:10 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3D_H
# define cub3D_H

# include "libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h> // to be removed!
//# include <string.h>

typedef struct s_map
{
	char	*texture_NO; // paths to textures
	char	*texture_SO;
	char	*texture_WE;
	char	*texture_EA;
	int		floor[3]; //rgb colours
	int		ceiling[3];
	char	**map;
}			t_map;

//parse
int	parse(t_map	*map, char *input, int x);

//init
void init_map(t_map	*map);

//error
void	print_example(char *temp);
void	identifier_error(int x);
void	colour_error(int i, int x, char **temp);

//utils
char	**add_array(char **input, char *entry, int y);
void	ft_free_split(char **array);
void	free_all(t_map	*map);
void	free_parse(int fd, char *temp);

#endif