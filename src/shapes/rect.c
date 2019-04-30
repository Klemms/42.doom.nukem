/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 03:38:40 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 00:32:34 by cababou          ###   ########.fr       */
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

void	draw_rect(t_doom *doom, SDL_Rect rect, SDL_Color color, int fill_rect)
{
	SDL_SetRenderDrawColor(doom->rend, color.r, color.g, color.b, color.a);
	if (fill_rect)
		SDL_RenderFillRect(doom->rend, &rect);
	else
		SDL_RenderDrawRect(doom->rend, &rect);
}
