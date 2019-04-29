/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_norme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:42:00 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 12:30:12 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	is_valid_2(t_wolf *w, int gres, int fd, char *line)
{
	if (gres < 0)
		exit_program(w, ERROR_READING_FILE);
	while ((gres = get_next_line(fd, &line)) > 0)
		if (line)
			lstcontainer_add(w->textures, line);
	if (gres < 0)
		exit_program(w, ERROR_READING_FILE);
	if ((w->map->height += 1) && lstcontainer_fastsize(w->textures) < 4)
		exit_program(w, ERROR_MAP_MISSING_TEXTURES);
	w->map->width += 2;
	close(fd);
}

int		is_valid(t_wolf *w, int fd)
{
	int		i;
	char	*line;
	int		gres;

	line = NULL;
	gres = 0;
	while (++w->map->height && (i = -1)
		&& (gres = get_next_line(fd, &line)) > 0)
	{
		if (line && ft_strcmp(line, "TEXTURES:") == 0)
		{
			ffree(line);
			break ;
		}
		while (line[++i] && line[i] != '\n')
			if (line[i] != '#' && line[i] != '.')
			{
				ffree(line);
				return (0);
			}
		w->map->width = (i > w->map->width ? i : w->map->width);
		ffree(line);
	}
	is_valid_2(w, gres, fd, line);
	return (1);
}
