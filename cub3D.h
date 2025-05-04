/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:00:37 by kfan              #+#    #+#             */
/*   Updated: 2025/05/04 14:57:58 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
	int		identifier[7];
	// flags in order for NO, SO, WE, EA, F ,C;
	// identifier[6] == 1 if parsing map started to throw newline error
	char	**map;
	int		flag;
	// to check enclosed map init as flag > 1 not enclosed, flag == 0 valid
}			t_map;

//for debugging, to be deleted
void	print_array(char **temp);
//parse
int		parse(t_map	*map, char *input, int x);
int		parse_line(t_map *map, char *temp, int line);
int		check_map(t_map *map, int gnl_flag, int line);
int		check_identifier(t_map *map, int error);
//init
int		init_map(t_map	*map, char *input);
//error
void	print_example(char *temp);
void	identifier_error(int x, int line);
void	colour_error(int i, int x, char **temp, int line);
//utils
char	**add_array(char **input, char *entry, int y);
char	**copy_map(char **map);
void	ft_free_split(char **array);
void	free_all(t_map	*map);
void	free_parse(int fd, char *temp);

#endif