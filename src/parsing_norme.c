/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_norme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:42:00 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 14:25:34 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	is_valid_2(t_doom *doom, int gres, int fd, char *line)
{
	if (gres < 0)
		exit_program(doom, ERROR_READING_FILE);
	while ((gres = get_next_line(fd, &line)) > 0)
		if (line)
			lstcontainer_add(doom->textures, line);
	if (gres < 0)
		exit_program(doom, ERROR_READING_FILE);
	if ((doom->map.height += 1) && lstcontainer_fastsize(doom->textures) < 4)
		exit_program(doom, ERROR_MAP_MISSING_TEXTURES);
	doom->map.width += 2;
	close(fd);
}

int		is_valid(t_doom *doom, int fd)
{
	int		i;
	char	*line;
	int		gres;

	line = NULL;
	gres = 0;
	while (++doom->map.height && (i = -1)
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
		doom->map.width = (i > doom->map.width ? i : doom->map.width);
		ffree(line);
	}
	is_valid_2(doom, gres, fd, line);
	return (1);
}
