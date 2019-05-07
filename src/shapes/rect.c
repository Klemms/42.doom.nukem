/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 03:38:40 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 15:35:32 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Rect	make_rect(int x, int y, int width, int height)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	return (rect);
}

void		draw_rect(SDL_Surface *s, SDL_Rect rect, SDL_Color color,
													int fill_rect)
{
	SDL_Rect rc;

	if (fill_rect)
		SDL_FillRect(s, &rect, rgba_to_int(color.r, color.g, color.b, color.a));
	else
	{
		rc = make_rect(rect.x, rect.y, rect.w, 1);
		SDL_FillRect(s, &rc, rgba_to_int(color.r, color.g, color.b, color.a));
		rc = make_rect(rect.x, rect.y + rect.h - 1, rect.w, 1);
		SDL_FillRect(s, &rc, rgba_to_int(color.r, color.g, color.b, color.a));
		rc = make_rect(rect.x, rect.y, 1, rect.h);
		SDL_FillRect(s, &rc, rgba_to_int(color.r, color.g, color.b, color.a));
		rc = make_rect(rect.x + rect.w - 1, rect.y, 1, rect.h);
		SDL_FillRect(s, &rc, rgba_to_int(color.r, color.g, color.b, color.a));
	}
}

void		draw_rect_u(SDL_Surface *s, SDL_Rect rect, Uint32 color,
														int fill_rect)
{
	SDL_Rect rc;

	if (fill_rect)
		SDL_FillRect(s, &rect, color);
	else
	{
		rc = make_rect(rect.x, rect.y, rect.w, 1);
		SDL_FillRect(s, &rc, color);
		rc = make_rect(rect.x, rect.y + rect.h - 1, rect.w, 1);
		SDL_FillRect(s, &rc, color);
		rc = make_rect(rect.x, rect.y, 1, rect.h);
		SDL_FillRect(s, &rc, color);
		rc = make_rect(rect.x + rect.w - 1, rect.y, 1, rect.h);
		SDL_FillRect(s, &rc, color);
	}
}
