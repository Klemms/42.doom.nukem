/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:13:25 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/05 12:29:59 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void		my_pixel_put(t_wolf *w, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < w->w_width && y < w->w_height)
		((unsigned int *)w->image->img)[x + y * w->w_width] = color;
}

static void				dx_dom(t_wolf *w, t_line *l)
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
		if ((l->inc.x > 0 && l->cur.x >= w->w_width)
		|| (l->inc.x < 0 && l->cur.x < 0) || (l->inc.y < 0 && l->cur.y < 0)
		|| (l->inc.y > 0 && l->cur.y >= w->w_height))
			break ;
		my_pixel_put(w, round(l->cur.x), round(l->cur.y), l->color);
	}
}

static void				dy_dom(t_wolf *w, t_line *l)
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
		if ((l->inc.x > 0 && l->cur.x >= w->w_width)
		|| (l->inc.x < 0 && l->cur.x < 0) || (l->inc.y < 0 && l->cur.y < 0)
		|| (l->inc.y > 0 && l->cur.y >= w->w_height))
			break ;
		my_pixel_put(w, round(l->cur.x), round(l->cur.y), l->color);
	}
}

void					line(t_wolf *w, t_vec *start, t_vec *end, int color)
{
	t_line *line;

	if (!(line = mmalloc(sizeof(t_line))))
		exit_program(w, ERROR_MEMORY);
	line->cur.x = start->x;
	line->cur.y = start->y;
	line->dir.x = end->x - start->x;
	line->dir.y = end->y - start->y;
	line->inc.x = (line->dir.x > 0) ? 1 : -1;
	line->inc.y = (line->dir.y > 0) ? 1 : -1;
	line->dir.x = fabs(line->dir.x);
	line->dir.y = fabs(line->dir.y);
	line->color = color;
	if (line->dir.x > line->dir.y)
		dx_dom(w, line);
	else
		dy_dom(w, line);
	ffree(line);
}
