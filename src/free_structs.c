/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 20:33:22 by cababou           #+#    #+#             */
/*   Updated: 2019/05/02 10:21:26 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_map(t_doom *doom)
{
	int		i;

	i = 0;
	if (doom->map.m)
	{
		while (i < doom->map.height)
		{
			ffree(doom->map.m[i]);
			i++;
		}
		ffree(doom->map.m);
	}
}

void	megafree_1(t_doom *doom)
{
	free_map(doom);
	Mix_FreeMusic(doom->scores.bgm);
	Mix_FreeChunk(doom->scores.walk);
	Mix_FreeChunk(doom->scores.shot);
}
