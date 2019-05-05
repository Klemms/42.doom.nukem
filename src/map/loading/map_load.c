/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 05:56:10 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 12:14:48 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	set_mapheader(t_nmap *m, int *header)
{
	m->size_x = header[0];
	m->size_y = header[1];
	m->skybox_color.r = header[2];
	m->skybox_color.g = header[3];
	m->skybox_color.b = header[4];
	m->skybox_color.a = header[5];
}

int		*get_mapheader(t_doom *d, char *l)
{
	char	*num;
	int		*header;
	int		i;
	int		nb;

	i = 0;
	if (!(header = mmalloc(sizeof(int) * 6))
		|| !(num = ft_strnew(0)))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	nb = 0;
	while (l[i])
	{
		if (l[i] == '[' || l[i] == ']')
		{
			i++;
			continue ;
		}
		if (l[i] == ',' && num && nb < 6)
		{
			header[nb++] = ft_atoi(num);
			free(num);
			num = ft_strnew(0);
		}
		if (ft_isnum(l[i]) || l[i] == '-')
			num = ft_charjoin(num, l[i], 1);
		i++;
	}
	return (header);
}

void	load_map(t_doom *d, char *path)
{
	t_nmap	*m;
	int		fd;
	char	*line;
	int		y;
	int		state;

	if (!(m = mmalloc(sizeof(t_nmap))))
		exit_program(d, ERROR_INVALID_MAP);
	m->map_name = path;
	if (!(fd = open(path, O_RDONLY | O_NOCTTY | O_NOFOLLOW)))
		exit_program(d, ERROR_INVALID_MAP);
	state = 0;
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (state == 0)
		{
			set_mapheader(m, get_mapheader(d, line));
			if(!(m->map = mmalloc(sizeof(t_mblock *) * m->size_y)))
				exit_program(d, ERROR_SDL_AFTER_INIT);
			state++;
		}
		else if (state == 1)
		{
			read_blockline(d, m, y, line);
			y++;
			if (y == m->size_y)
				state++;
		}
		else if (state == 2)
		{
			y = ft_atoi(line);
			m->textures = lstcontainer_new();
			state++;
		}
		else if (state == 3)
		{
			read_texture(d, m, line);
			y--;
			if (y < 0)
				break;
		}
		/*free(line);
		line = NULL;*/
	}
	while (get_next_line(fd, &line) > 0)
		continue ;
}
