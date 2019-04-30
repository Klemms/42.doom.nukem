/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 20:33:22 by cababou           #+#    #+#             */
/*   Updated: 2019/04/29 21:49:53 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_player(t_doom *doom)
{
	ffree(doom->you->pos);
	ffree(doom->you->dir);
	ffree(doom->you->plane);
	ffree(doom->you);
}

void	free_map(t_doom *doom)
{
	int		i;

	i = 0;
	if (doom->map->m)
	{
		while (i < doom->map->height)
		{
			ffree(doom->map->m[i]);
			i++;
		}
		ffree(doom->map->m);
	}
	ffree(doom->map);
}

void	free_sight(t_doom *doom)
{
	if (doom->sight->pos)
		ffree(doom->sight->pos);
	ffree(doom->sight);
}

void	megafree_1(t_doom *doom)
{
	if (doom->textures && doom->textures->firstelement)
		ft_lstdel(doom->textures->firstelement, 1);
	ffree(doom->textures);
	ffree(doom->keys);
	doom->keys = NULL;
	if (doom->you)
		free_player(doom);
	free_map(doom);
	ffree(doom);
}
