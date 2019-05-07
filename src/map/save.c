/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 00:02:20 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 05:09:23 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ed_save_file(t_doom *d, t_el_button *b, SDL_MouseButtonEvent ev)
{
	b->is_disabled = 1;
	ft_putendl("Saving file...");
	ft_putendl(d->nmap->map_name);
	write_map(d->nmap, d->nmap->map_name);
	b->is_disabled = 0;
	ft_putendl("Finished");
}

int		validm(t_nmap *m, t_validate *val)
{
	if ((val->y == 0 || val->y == m->size_y - 1 || val->x == 0
			|| val->x == m->size_x - 1)
		&& m->map[val->y][val->x].block_type != block_wall)
		return (map_wall_contour);
	if (m->map[val->y][val->x].block_type == block_spawn)
		val->spawn_points++;
	if (m->map[val->y][val->x].block_type == block_end)
		val->end_points++;
	return (0);
}

int		validate_map(t_doom *d, t_nmap *m)
{
	t_validate	validate;
	int			status;

	validate.spawn_points = 0;
	validate.end_points = 0;
	validate.y = 0;
	while (validate.y < m->size_y)
	{
		validate.x = 0;
		while (validate.x < m->size_x)
		{
			if ((status = validm(m, &validate)) > 0)
				return (status);
			validate.x++;
		}
		validate.y++;
	}
	if (validate.spawn_points != 1)
		return (map_spawn_point);
	if (validate.end_points < 1)
		return (map_end_point);
	return (map_good);
}

void	ed_test_map(t_doom *d, t_el_button *b, SDL_MouseButtonEvent ev)
{
	int		result;

	if (ev.button == SDL_BUTTON_LEFT)
	{
		b->is_disabled = 1;
		result = validate_map(d, d->nmap);
		free(d->editor.state->text);
		d->editor.state->text = ft_strdup(map_reason_to_txt(result));
		if (result > 0)
			ft_putchar('\a');
		text_prepare(d, d->editor.state, 1, 1);
		b->is_disabled = 0;
	}
}
