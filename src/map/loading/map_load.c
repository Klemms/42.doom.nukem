/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 05:56:10 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 05:10:15 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	load_map_2(t_doom *d, int fd, t_nmap *m, int *y)
{
	char	*line;
	int		state;

	state = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (state == 0)
			lm_1(d, &state, m, line);
		else if (state == 1)
		{
			read_blockline(d, m, *y, line);
			lm_2(y, &state, m, line);
		}
		else if (state == 2)
			lm_3(y, &state, m, line);
		else if (state == 3)
		{
			read_texture(d, m, line);
			*y = *y - 1;
			if (*y < 0)
				break ;
		}
	}
}

t_nmap	*load_map(t_doom *d, char *path)
{
	char	*line;
	t_nmap	*m;
	int		fd;
	int		y;

	if (!(m = mmalloc(sizeof(t_nmap))))
		exit_program(d, ERROR_INVALID_MAP);
	m->map_name = ft_strdup(path);
	if ((fd = open(path, O_RDONLY | O_NOCTTY | O_NOFOLLOW)) < 0)
		exit_program(d, ERROR_INVALID_MAP);
	y = 0;
	load_map_2(d, fd, m, &y);
	while (get_next_line(fd, &line) > 0)
	{
		free(line);
		line = NULL;
	}
	return (m);
}
