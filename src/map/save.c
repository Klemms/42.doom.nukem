/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 00:02:20 by cababou           #+#    #+#             */
/*   Updated: 2019/05/04 03:21:40 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ed_save_file(t_doom *d, t_el_button *b, SDL_MouseButtonEvent ev)
{
	b->is_disabled = 1;
	ft_putendl("Saving file...");
	write_map(d->nmap, d->nmap->map_name);
	b->is_disabled = 0;
	ft_putendl("Finished");
}

int		validate_map(t_nmap	*m)
{
	size_t	x;
	size_t	y;
	int		spawn_points;
	int		end_points;

	read_map("maps/test.nmap");

	x = 0;
	spawn_points = 0;
	end_points = 0;
	while (x < m->size_x)
	{
		y = 0;
		while (y < m->size_y)
		{
			if ((y == 0 || y == m->size_y - 1 || x == 0 || x == m->size_x - 1)
				&& m->map[x][y].block_type != block_wall)
				return (map_wall_contour);
			if (m->map[x][y].block_type == block_spawn)
				spawn_points++;
			if (m->map[x][y].block_type == block_end)
				end_points++;
			y++;
		}
		x++;
	}
	if (spawn_points != 1)
		return (map_spawn_point);
	if (end_points < 1)
		return (map_end_point);
	return (map_good);
}

void	ed_test_map(t_doom *d, t_el_button *b, SDL_MouseButtonEvent ev)
{
	int		result;

	if (ev.button == SDL_BUTTON_LEFT)
	{
		b->is_disabled = 1;
		result = validate_map(d->nmap);
		free(d->editor.state->text);
		d->editor.state->text = ft_strdup(map_reason_to_txt(result));
		if (result > 0)
			ft_putchar('\a');
		text_prepare(d, d->editor.state, 1, 1);
		b->is_disabled = 0;
	}
}
