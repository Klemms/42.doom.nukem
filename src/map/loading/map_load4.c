/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 06:57:48 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 07:13:47 by cababou          ###   ########.fr       */
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
		|| !(num = ft_strnew(0, 0)))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	nb = 0;
	while (l[i])
	{
		if (l[i] == ',' && num && nb < 6)
		{
			header[nb++] = ft_atoi(num);
			free(num);
			num = ft_strnew(0, 0);
		}
		if (ft_isnum(l[i]) || l[i] == '-')
			num = ft_charjoin(num, l[i], 1);
		i++;
	}
	free(num);
	free(header);
	return (header);
}

void	lm_1(t_doom *d, int *state, t_nmap *m, char *line)
{
	set_mapheader(m, get_mapheader(d, line));
	free(line);
	if (!(m->map = mmalloc(sizeof(t_mblock *) * m->size_y)))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	*state = *state + 1;
}

void	lm_2(int *y, int *state, t_nmap *m, char *line)
{
	*y = *y + 1;
	if (*y == m->size_y)
		*state = *state + 1;
}

void	lm_3(int *y, int *state, t_nmap *m, char *line)
{
	*y = ft_atoi(line);
	m->textures = lstcontainer_new();
	free(line);
	*state = *state + 1;
}
