/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 02:55:07 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 06:24:30 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Uint32		color_to_uint(SDL_Color color)
{
	return (Uint32)((color.r << 16) + (color.g << 8) + (color.b << 0));
}

int			mouse_in(int m_x, int m_y, SDL_Rect rect)
{
	if (m_x >= rect.x && m_x < rect.x + rect.w)
		if (m_y >= rect.y && m_y < rect.y + rect.h)
			return (1);
	return (0);
}

int			is_left_clicking(void)
{
	return (SDL_GetMouseState(NULL, NULL) == SDL_BUTTON_LMASK);
}

int			is_right_clicking()
{
	return (SDL_GetMouseState(NULL, NULL) == SDL_BUTTON_RMASK);
}

SDL_Rect	mouse_pos()
{
	int	x;
	int	y;

	SDL_GetMouseState(&x, &y);
	return (make_rect(x, y, 0, 0));
}
