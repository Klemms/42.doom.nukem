/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:21:11 by cababou           #+#    #+#             */
/*   Updated: 2019/03/19 18:22:38 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_limit_fps(unsigned int limit)
{
	unsigned int	ticks;

	ticks = SDL_GetTicks();
	if (ticks > limit)
		return ;
	else if (ticks + 16 < limit)
		SDL_Delay(FPS_LIMIT);
	else
		SDL_Delay(limit - ticks);
}
