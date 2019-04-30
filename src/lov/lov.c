/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:20:18 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/30 14:24:48 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom.h"

int					calc_column(t_sight *p, t_doom *doom, int tex)
{
	double	col;

	if (p->side == 1)
		col = p->pos.x + p->perp_wall_dist * p->ray_dir.x;
	else
		col = p->pos.y + p->perp_wall_dist * p->ray_dir.y;
	col = col - floor(col);
	col = round(col * (double)(doom->texture[tex].width - 1));
	if ((p->side == 0 && p->ray_dir.x > 0)
	|| (p->side == 1 && p->ray_dir.y < 0))
		col = doom->texture[tex].width - col - 1;
	return (col);
}

void				calc_perp_dist(t_sight *p, t_player *you)
{
	if (p->side == 0)
		p->perp_wall_dist = ((int)p->pos.x - you->pos.x
			+ (1.0 - p->step.x) / 2.0) / p->ray_dir.x;
	else
		p->perp_wall_dist = ((int)p->pos.y - you->pos.y
			+ (1.0 - p->step.y) / 2.0) / p->ray_dir.y;
}

void				calc_lov(t_doom *doom)
{
	int		x;
	int		column;
	int		tex;

	x = 0;
//	printf("10\n");
	while (x < doom->w_width)
	{
//		printf("11\n");
		init_sight(doom, &doom->sight, x, &doom->you);
//		printf("12\n");
		if (see_wall(&doom->sight, doom))
		{
//			printf("13\n");
			if (doom->sight.side == 1)
				tex = doom->sight.step.y < 0;
			else
				tex = (doom->sight.step.x < 0 ? 2 : 3);
//			printf("14\n");
			column = calc_column(&doom->sight, doom, tex);
//			printf("15\n");
			draw_wall(doom, x, column, tex);
		}
//		printf("16\n");
		x++;
//		printf("18\n");
	}
//	printf("19\n");
}
