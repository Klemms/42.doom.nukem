/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 05:56:10 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 09:54:00 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	load_map_3(t_doom *d, char *line, t_nmap *m, int *state)
{
	if (*state == 4)
	{
		m->sprites = lstcontainer_new();
		if (ft_isnum(line[0]))
			m->spritecount = ft_atoi(line, 0);
		else
			exit_program(d, ERROR_INVALID_MAP);
		*state = *state + 1;
		free(line);
	}
	else if (*state == 5)
	{
		read_sprites(d, m, line);
		m->spritecount--;
		if (m->spritecount < 0)
			*state = *state + 1;
	}
}

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
			if ((*y = *y - 1) <= 0)
				state++;
		}
		else
			load_map_3(d, line, m, &state);
	}
}

t_sprite	*make_doorwindowsprite(t_doom *d, t_mblock *b)
{
	t_sprite	*sprite;

	if (!(sprite = mmalloc(sizeof(t_sprite))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	sprite->dontsave = 1;
	sprite->pos.x = b->x;
	sprite->pos.y = b->y;
	sprite->texture = b->n_texture;
	sprite->texture_back = b->s_texture;
	sprite->render_mode = b->block_type
		== block_door ? rend_door : rend_window;
	return (sprite);
}

void	make_doorwindows(t_doom *d, t_nmap *m)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < m->size_y)
	{
		x = 0;
		while (x < m->size_x)
		{
			if (m->map[y][x].block_type == block_door
				|| m->map[y][x].block_type == block_window)
			{

				lstcontainer_add(m->sprites,
					make_doorwindowsprite(d, &m->map[y][x]));
			}
			x++;
		}
		y++;
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
	make_doorwindows(d, m);
	return (m);
}
