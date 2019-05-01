/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:21:38 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/01 02:31:12 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		fill_2(t_doom *doom, int gres, int fd, t_map *map)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	line = NULL;
	while ((gres = get_next_line(fd, &line)) > 0)
	{
		if (!(map->m[++j] = mmalloc(sizeof(char) * (map->width + 1))))
			exit_program(doom, ERROR_MEMORY);
		if (line && ft_strcmp(line, "TEXTURES:") == 0)
		{
			ffree(line);
			break ;
		}
		i = -1;
		while (line[++i])
			map->m[j][i + 1] = line[i];
		i--;
		while (++i < map->width - 2)
			map->m[j][i + 1] = '#';
		map->m[j][map->width] = '\0';
		ffree(line);
	}
	return (gres);
}

static void		fill(t_doom *doom, t_map *map, int fd)
{
	int		gres;

	gres = 0;
	if (!(map->m = mmalloc(sizeof(char *) * (map->height + 1))))
		exit_program(doom, ERROR_MEMORY);
	map->m[map->height] = NULL;
	gres = fill_2(doom, gres, fd, map);
	close(fd);
	if (gres < 0)
		exit_program(doom, ERROR_READING_FILE);
}

static void		contour(t_doom *doom, t_map *map)
{
	int		i;
	int		width;
	int		height;

	width = map->width;
	height = map->height;
	i = -1;
	ffree(map->m[height - 1]);
	if (!(map->m[0] = mmalloc(sizeof(char) * (width + 1)))
		|| !(map->m[height - 1] = mmalloc(sizeof(char) * (width + 1))))
		exit_program(doom, ERROR_MEMORY);
	while (++i < width)
	{
		map->m[0][i] = '#';
		map->m[height - 1][i] = '#';
	}
	i = -1;
	while (++i < height)
	{
		map->m[i][0] = '#';
		map->m[i][width - 1] = '#';
	}
	map->m[0][width] = '\0';
	map->m[height - 1][width] = '\0';
}

static int		startpos(t_map *map, char c)
{
	int		x;
	int		y;

	y = map->height;
	while (--y >= 0 && map->start_x == 0)
	{
		x = map->width;
		while (--x >= 0 && map->start_x == 0)
		{
			if (map->m[y][x] == c)
			{
				map->start_x = x;
				map->start_y = y;
			}
		}
	}
	return (map->start_x != 0);
}

int				parsing(t_doom *doom, char *file)
{
	int		fd[2];

	doom->map.map_name = file;
	if ((fd[0] = open(file, O_RDONLY)) < 2
	|| (read(fd[0], NULL, 0) < 0))
		return (0);
	fd[1] = open(file, O_RDONLY);
	if (is_valid(doom, fd[0]))
	{
		fill(doom, &doom->map, fd[1]);
		contour(doom, &doom->map);
		if (!startpos(&doom->map, '.'))
			return (0);
		return (1);
	}
	return (0);
}
