/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 23:11:15 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 23:22:20 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Uint32				calc_gradient(Uint32 color1, Uint32 color2, double stage)
{
	return (((Uint32)((((color1 >> 16) & 0xFF) + ((color2 >> 16) & 0xFF))
		* stage) << 16)
			| ((Uint32)((((color1 >> 8) & 0xFF) + ((color2 >> 8) & 0xFF))
				* stage) << 8)
			| ((Uint32)(((color1 & 0xFF) + (color2 & 0xFF)) * stage)));
}

void				swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void				combsort2(int *amount, t_norme1 *norm,
	int *order, double *dist)
{
	int			i;
	int			j;

	i = -1;
	while (++i < *amount - norm->gap)
	{
		j = i + norm->gap;
		if (dist[i] < dist[j])
		{
			norm->tmp = dist[i];
			dist[i] = dist[j];
			dist[j] = norm->tmp;
			norm->tmp = order[i];
			order[i] = order[j];
			order[j] = norm->tmp;
			norm->swapped = 1;
		}
	}
}

void				combsort(int *order, double *dist, int amount)
{
	t_norme1	norm;

	norm.gap = amount;
	norm.swapped = 0;
	while (norm.gap > 1 || norm.swapped)
	{
		norm.gap = (norm.gap * 10) / 13;
		if (norm.gap == 9 || norm.gap == 10)
			norm.gap = 11;
		if (norm.gap < 1)
			norm.gap = 1;
		norm.swapped = 0;
		combsort2(&amount, &norm, order, dist);
	}
}
