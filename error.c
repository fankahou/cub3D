/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2025/05/01 19:12:38 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_example(char *temp)
{
	if (temp)
		write(2, temp, ft_strlen(temp));
	write(1, ".cub example: \n", 15);
	write(1, "NO ./path_to_the_north_texture\n", 31);
	write(1, "SO ./path_to_the_south_texture\n", 31);
	write(1, "WE ./path_to_the_west_texture\n", 30);
	write(1, "EA ./path_to_the_east_texture\n\n", 31);
	write(1, "F 220,100,0\n", 12);
	write(1, "C 225,30,0\n\n", 12);
	write(1, "(here starts the enclosed map)\n", 31);
}

void	identifier_error(int x)
{
	if (x == 0)
		write(2, "line 1 should start with \"NO ./\"\n", 33);
	if (x == 1)
		write(2, "line 2 should start with \"SO ./\"\n", 33);
	if (x == 2)
		write(2, "line 3 should start with \"WE ./\"\n", 33);
	if (x == 3)
		write(2, "line 4 should start with \"EA ./\"\n", 33);
	if (x == 4)
		write(2, "line 5 should be empty (newline)\n", 33);
	if (x == 5)
		write(2, "line 6 should start with identifier \"F\"\n", 40);
	if (x == 6)
		write(2, "line 7 should start with identifier \"C\"\n", 40);
	if (x == 7)
		write(2, "line 8 should be empty (newline)\n", 33);
	print_example(NULL);
}

void	colour_error(int i, int x, char **temp)
{
	ft_free_split(temp);
	if (x == 5)
		write(2, "line 6: ", 8);
	else if (x == 6)
		write(2, "line 7: ", 8);
	if (i == 0)
		write(2, "fisrt colour ", 13);
	else if (i == 1)
		write(2, "second colour ", 14);
	else if (i == 2)
		write(2, "third colour ", 13);
	else if (i == 3)
		write(2, "there should only be 3 numbers\n", 31);
	if (i < 3)
		write(2, "should be in the range of 0 - 255\n", 34);
	print_example(NULL);
}
