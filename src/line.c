/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:13:25 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/30 17:14:57 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void				dx_dom(t_doom *doom, t_line *l)
{
	double		stack;
	int			i;

	stack = l->dir.x / 2.0;
	i = 0;
	while (++i <= l->dir.x)
	{
		l->cur.x += l->inc.x;
		stack += l->dir.y;
		if (stack >= l->dir.x)
		{
			stack -= l->dir.x;
			l->cur.y += l->inc.y;
		}
		if ((l->inc.x > 0 && l->cur.x >= doom->settings.window_width)
		|| (l->inc.x < 0 && l->cur.x < 0) || (l->inc.y < 0 && l->cur.y < 0)
		|| (l->inc.y > 0 && l->cur.y >= doom->settings.window_height))
			break ;
		pixel_put(doom, round(l->cur.x), round(l->cur.y), l->color);
	}
}

static void				dy_dom(t_doom *doom, t_line *l)
{
	double		stack;
	int			i;

	stack = l->dir.y / 2.0;
	i = 0;
	while (++i <= l->dir.y)
	{
		l->cur.y += l->inc.y;
		stack += l->dir.x;
		if (stack >= l->dir.y)
		{
			stack -= l->dir.y;
			l->cur.x += l->inc.x;
		}
		if ((l->inc.x > 0 && l->cur.x >= doom->settings.window_width)
		|| (l->inc.x < 0 && l->cur.x < 0) || (l->inc.y < 0 && l->cur.y < 0)
		|| (l->inc.y > 0 && l->cur.y >= doom->settings.window_height))
			break ;
		pixel_put(doom, round(l->cur.x), round(l->cur.y), l->color);
	}
}

void					line(t_doom *doom, t_vec *start, t_vec *end, int color)
{
	t_line line;

	line.cur.x = start->x;
	line.cur.y = start->y;
	line.dir.x = end->x - start->x;
	line.dir.y = end->y - start->y;
	line.inc.x = (line.dir.x > 0) ? 1 : -1;
	line.inc.y = (line.dir.y > 0) ? 1 : -1;
	line.dir.x = fabs(line.dir.x);
	line.dir.y = fabs(line.dir.y);
	line.color = color;
	if (line.dir.x > line.dir.y)
		dx_dom(doom, &line);
	else
		dy_dom(doom, &line);
}
