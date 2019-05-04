/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 20:33:22 by cababou           #+#    #+#             */
/*   Updated: 2019/05/04 09:09:35 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_map(t_doom *doom)
{
	int		i;

	i = 0;
	if (doom->old_map.m)
	{
		while (i < doom->old_map.height)
		{
			ffree(doom->old_map.m[i]);
			i++;
		}
		ffree(doom->old_map.m);
	}
}

void	megafree_1(t_doom *doom)
{
	free_map(doom);
	Mix_FreeMusic(doom->scores.bgm);
	Mix_FreeChunk(doom->scores.walk);
	Mix_FreeChunk(doom->scores.shot);
}
