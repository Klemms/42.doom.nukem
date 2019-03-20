/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:43:09 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/13 16:19:09 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	ft_clamp(double a, double min, double max)
{
	if (a > min)
	{
		if (a < max)
			return (a);
		return (max);
	}
	return (min);
}

double	ft_point_side(t_xy p, t_xy p1, t_xy p2)
{
	double	side;

	side = (((p2.x - p1.x) * (p.y - p1.y)) - ((p.x - p1.x) * (p2.y - p1.y)));
	return (side);
}

int		ft_intersect_box(t_xy p1, t_xy p2, t_xy p3, t_xy p4)
{
	t_xy	x_p1_p2;
	t_xy	x_p3_p4;
	t_xy	y_p1_p2;
	t_xy	y_p3_p4;

	x_p1_p2.x = (p1.x < p2.x) ? p1.x : p2.x;
	x_p1_p2.y = (p1.x > p2.x) ? p1.x : p2.x;
	x_p3_p4.x = (p3.x < p4.x) ? p3.x : p4.x;
	x_p3_p4.y = (p3.x > p4.x) ? p3.x : p4.x;
	if (x_p1_p2.x <= x_p3_p4.y && x_p3_p4.x <= x_p1_p2.y)
	{
		y_p1_p2.x = (p1.y < p2.y) ? p1.y : p2.y;
		y_p1_p2.y = (p1.y > p2.y) ? p1.y : p2.y;
		y_p3_p4.x = (p3.y < p4.y) ? p3.y : p4.y;
		y_p3_p4.y = (p3.y > p4.y) ? p3.y : p4.y;
		if (y_p1_p2.x <= y_p3_p4.y && y_p3_p4.x <= y_p1_p2.y)
			return (1);
	}
	return (0);
}
