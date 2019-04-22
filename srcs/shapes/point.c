/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 03:52:05 by cababou           #+#    #+#             */
/*   Updated: 2019/04/22 03:52:52 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_point(t_doom *doom, int x, int y, SDL_Color color)
{
	SDL_SetRenderDrawColor(doom->rend, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(doom->rend, x, y);
}
