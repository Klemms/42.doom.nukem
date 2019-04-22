/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:28:56 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/22 05:02:19 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_print_x_wall(t_doom *doom, int x, int y1, int y2, int top, int middle, int bottom)
{
	int		y;
	Uint32	*data;

	data = doom->render_pixels;
    y1 = ft_clamp(y1, 0, doom->settings->window_height-1);
    y2 = ft_clamp(y2, 0, doom->settings->window_height-1);
    if(y2 == y1)
        data[y1 * doom->settings->window_width + x] = middle;
    else if(y2 > y1)
    {
        data[y1 * doom->settings->window_width + x] = top;
		y = y1;
		while (++y < y2)
			data[y * doom->settings->window_width + x] = middle;
        data[y2 * doom->settings->window_width + x] = bottom;
    }
}

void	ft_coord_wall(t_doom *doom, t_raycasting *r)
{
	/* Acquérir les coordonnées x, y des deux extrémités (sommets) de cette arête du secteur */
	r->v1.x = r->sect->vertex[r->i].x - doom->player.where.x;
	r->v1.y = r->sect->vertex[r->i].y - doom->player.where.y;
	r->v2.x = r->sect->vertex[r->i + 1].x - doom->player.where.x;
	r->v2.y = r->sect->vertex[r->i + 1].y - doom->player.where.y;
	/* Faites-les pivoter autour de la vue du joueur */
	r->p_cos = doom->player.anglecos;
	r->p_sin = doom->player.anglesin;
	r->t1.x = r->v1.x * r->p_sin - r->v1.y * r->p_cos;
	r->t1.y = r->v1.x * r->p_cos + r->v1.y * r->p_sin;
	r->t2.x = r->v2.x * r->p_sin - r->v2.y * r->p_cos;
	r->t2.y = r->v2.x * r->p_cos + r->v2.y * r->p_sin;
}

void	ft_position_wall2(t_raycasting *r)
{
	// Trouver une intersection entre le mur et les bords approximatifs de la vue du joueur
//	r->t1.x = -1;
//	r->t1.y = 2;
//	r->t2.x = 1;
//	r->t2.y = -1;
	r->near.x = 2;
	r->near.y = 1;
	r->far.x = -2;
	r->far.y = -2;
	r->i1 = ft_intersect_lines(r->t1, r->t2, r->near, r->far);
//	printf("test i1: %f %f\n", r->i1.x, r->i1.y);
	
	r->near.x = -0.00001;
	r->near.y = 0.0001;
	r->far.x = -20.0;
	r->far.y = 5.0;
//	printf("t1: %f %f  t2: %f %f\n", r->t1.x, r->t1.y, r->t2.x, r->t2.y);
	r->i1 = ft_intersect_lines(r->t1, r->t2, r->near, r->far);

	r->near.x *= -1;
	r->far.x *= -1;
	r->i2 = ft_intersect_lines(r->t1, r->t2, r->near, r->far);
	if (r->t1.y < r->near.y)
	{
//		printf("av OUI: %f %f\n", r->t1.x, r->t1.y);
//		printf("i1: %f %f  i2: %f %f\n", r->i1.x, r->i1.y, r->i2.x, r->i2.y);
		if (r->i1.y > 0)
		{
//			printf("1\n");
			r->t1.x = r->i1.x;
			r->t1.y = r->i1.y;
		}
		else
		{
//			printf("2\n");
			r->t1.x = r->i2.x;
			r->t1.y = r->i2.y;
		}
//		printf("ap OUI: %f %f\n", r->t1.x, r->t1.y);
	}
}

void	ft_position_wall(t_doom *doom, t_raycasting *r)
{
	/* Le mur est-il au moins partiellement devant le joueur? */
//	printf("avant OUI: %f\n", r->t1.y);
	if(r->t1.y <= 0 || r->t2.y <= 0)
	{
		ft_position_wall2(r);
		if (r->t2.y < r->near.y)
		{
			if (r->i1.y > 0)
			{
				r->t2.x = r->i1.x;
				r->t2.y = r->i1.y;
			}
			else
			{
				r->t2.x = r->i2.x;
				r->t2.y = r->i2.y;
			}
		}
	}
	/* Faire la transformation de perspective */
	r->scale1.x = doom->settings->angle_h / r->t1.y;
	r->scale1.y = doom->settings->angle_v / r->t1.y;
	r->scale2.x = doom->settings->angle_h / r->t2.y;
	r->scale2.y = doom->settings->angle_v / r->t2.y;
	r->lim_x.x = (doom->settings->window_width / 2) - (int)(r->t1.x * r->scale1.x);
	r->lim_x.y = (doom->settings->window_width / 2) - (int)(r->t2.x * r->scale2.x);
}

void	ft_coord_ceil_floor(t_doom *doom, t_raycasting *r)
{
	/* Acquérir les hauteurs de plancher et de plafond, par rapport à la vue du joueur */
	r->y_ceil = r->sect->ceil - doom->player.where.z;
	r->y_floor = r->sect->floor - doom->player.where.z;
	/* Vérifiez le type de bord. voisin = -1 signifie mur, autre = frontière entre deux secteurs. */
	r->neighbor = r->sect->neighbors[r->i];
	r->ny_ceil = 0;
	r->ny_floor = 0;
	// Un autre secteur apparaît-il sur ce portail?
	if(r->neighbor >= 0)
	{
		r->ny_ceil  = doom->sectors[r->neighbor].ceil  - doom->player.where.z;
		r->ny_floor = doom->sectors[r->neighbor].floor - doom->player.where.z;
	}
	/* Projeter nos hauteurs de plafond et de plancher en coordonnées d'écran (coordonnée en Y) */
	r->y1.x = (doom->settings->window_height / 2) - (int)((doom->player.yaw * r->t1.y + r->y_ceil)
		* r->scale1.y);
	r->y1.y = (doom->settings->window_height / 2) - (int)((doom->player.yaw * r->t1.y + r->y_floor)
		* r->scale1.y);
	r->y2.x = (doom->settings->window_height / 2) - (int)((doom->player.yaw * r->t2.y + r->y_ceil)
		* r->scale2.y);
	r->y2.y = (doom->settings->window_height / 2) - (int)((doom->player.yaw * r->t2.y + r->y_floor)
		* r->scale2.y);
	/* Même chose pour le secteur voisin */
	r->n_y1.x = (doom->settings->window_height / 2) - (int)((doom->player.yaw * r->t1.y + r->ny_ceil)
		* r->scale1.y);
	r->n_y1.y = (doom->settings->window_height / 2) - (int)((doom->player.yaw * r->t1.y + r->ny_floor)
		* r->scale1.y);
	r->n_y2.x = (doom->settings->window_height / 2) - (int)((doom->player.yaw * r->t2.y + r->ny_ceil)
		* r->scale2.y);
	r->n_y2.y = (doom->settings->window_height / 2) - (int)((doom->player.yaw * r->t2.y + r->ny_floor)
		* r->scale2.y);
}

void	ft_other_sector(t_doom *doom, t_raycasting *r)
{
	/* Y a-t-il un autre secteur derrière ce bord? */
	if(r->neighbor >= 0)
	{
		/* Pareil pour le sol et le plafond */
		r->n_y.x = (r->x - r->lim_x.x) * (r->n_y2.x-r->n_y1.x) / (r->lim_x.y-r->lim_x.x) + r->n_y1.x;
		r->c_n_y.x = ft_clamp(r->n_y.x, r->y_top[r->x],r->y_bot[r->x]);
		r->n_y.y = (r->x - r->lim_x.x) * (r->n_y2.y-r->n_y1.y) / (r->lim_x.y-r->lim_x.x) + r->n_y1.y;
		r->c_n_y.y = ft_clamp(r->n_y.y, r->y_top[r->x],r->y_bot[r->x]);
		r->color_ceil = (r->x==r->lim_x.x||r->x==r->lim_x.y) ? 0 : 0x010101 * (255 - r->z);
		r->color_floor = (r->x==r->lim_x.x||r->x==r->lim_x.y) ? 0 : 0x040007 * (31 - r->z / 8);
		/* Si notre plafond est plus élevé que leur plafond, rendez mur supérieur */
		// Entre notre et leur plafond
		ft_print_x_wall(doom, r->x, r->c_y.x, r->c_n_y.x - 1, 0, r->color_ceil, 0);
		// Réduire la fenêtre restante au-dessous de ces plafonds
		if (r->c_y.x < r->c_n_y.x)
			r->c_y.x = r->c_n_y.x;
		r->y_top[r->x] = ft_clamp(r->c_y.x, r->y_top[r->x], doom->settings->window_height-1);
		/* Si notre sol est plus bas que le sol, rendez le mur du bas */
		// Entre leur et notre sol
		ft_print_x_wall(doom, r->x, r->c_n_y.y + 1, r->c_y.y, 0, r->color_floor, 0);
		//Réduire la fenêtre restante au-dessus de ces sol
		if (r->c_y.y > r->c_n_y.y)
			r->c_y.y = r->c_n_y.y;
		r->y_bot[r->x] = ft_clamp(r->c_y.y, 0, r->y_bot[r->x]);
	}
	else
	{
		/* Il n'y a pas de voisin. Rendu du mur du haut (cya = niveau du plafond) vers le bas (cyb = niveau du sol). */
		r->color_wall = (r->x==r->lim_x.x||r->x==r->lim_x.y) ? 0 : 0x010101 * (255 - r->z);
		ft_print_x_wall(doom, r->x, r->c_y.x, r->c_y.y, 0, r->color_wall, 0);
	}
}

void	ft_render_wall(t_doom *doom, t_raycasting *r)
{
	/* Rendu du mur */
	r->x_start_end.x = (r->lim_x.x > r->now.x1) ? r->lim_x.x : r->now.x1;
	r->x_start_end.y = (r->lim_x.y < r->now.x2) ? r->lim_x.y : r->now.x2;
	r->x = r->x_start_end.x - 1;
	while (++r->x <= r->x_start_end.y)
	{
		/* Calculez la coordonnée Z pour ce point. (Utilisé uniquement pour l'éclairage.) */
		r->z = ((r->x - r->lim_x.x) * (r->t2.y - r->t1.y)
			/ (r->lim_x.y - r->lim_x.x) + r->t1.y) * 8;
		r->z = ft_clamp(r->z, 0, 255);
		/* Acquérir les coordonnées Y pour notre plafond et le sol pour cette coordonnée X. Les pince. */
		// top
		r->y.x = (r->x - r->lim_x.x) * (r->y2.x - r->y1.x)
			/ (r->lim_x.y - r->lim_x.x) + r->y1.x;
		r->c_y.x = ft_clamp(r->y.x, r->y_top[r->x], r->y_bot[r->x]);
		// bottom
		r->y.y = (r->x - r->lim_x.x) * (r->y2.y - r->y1.y)
			/ (r->lim_x.y - r->lim_x.x) + r->y1.y;
		r->c_y.y = ft_clamp(r->y.y, r->y_top[r->x], r->y_bot[r->x]);
		/* Render plafond: tout ce qui dépasse la hauteur de plafond de ce secteur. */
		ft_print_x_wall(doom, r->x, r->y_top[r->x], r->c_y.x - 1, 0x111111, 0x222222, 0x111111);
		/* Render floor: tout en dessous de la hauteur de plancher de ce secteur. */
		ft_print_x_wall(doom, r->x, r->c_y.y + 1, r->y_bot[r->x], 0x0000FF, 0x0000AA, 0x0000FF);
		/* Y a-t-il un autre secteur derrière ce bord? */
		ft_other_sector(doom, r);
	}
	/* Planifiez le rendu du secteur voisin dans la fenêtre formée par ce mur. */
	if (r->neighbor >= 0 && r->x_start_end.y >= r->x_start_end.x
		&& (r->head + MAX_WAIT + 1 - r->tail) % MAX_WAIT)
	{
		*r->head = (t_window){r->neighbor, r->x_start_end.x, r->x_start_end.y};
		if (++r->head == r->wait + MAX_WAIT)
			r->head = r->wait;
	}
}

void	ft_print_screen(t_doom *doom)
{
	t_raycasting	r;
	int				render_sector[doom->num_sectors];

	if (!(r.y_top = mmalloc(sizeof(int) * (doom->settings->window_width + 1))))
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);
	if (!(r.y_bot = mmalloc(sizeof(int) * (doom->settings->window_width + 1))))
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);
	r.head = r.wait;
	r.tail = r.wait;
	r.i = doom->settings->window_width;
	while (--r.i >= 0)
	{
		r.y_top[r.i] = 0;
		r.y_bot[r.i] = doom->settings->window_height - 1;
	}
	while (++r.i < doom->num_sectors)
		render_sector[r.i] = 0;
    /* Commencez le rendu sur tout l'écran à partir de l'endroit où se trouve le lecteur. */
	*r.head = (t_window) {doom->player.sector, 0, doom->settings->window_width - 1};
    if (++r.head == r.wait + MAX_WAIT)
		r.head = r.wait;
//	printf("%d\n", doom->player.sector);
	// rendre tous les autres secteurs en file d'attente
    while (r.head != r.tail)
	{
		/* Choisissez un secteur et une tranche dans la file d'attente pour dessiner */
		r.now = *r.tail;
		if (++r.tail == r.wait + MAX_WAIT)
			r.tail = r.wait;
		// Odd = toujours rendu, 0x20 = abandonner
		if (render_sector[r.now.sector] & 0x21)
			continue;
		++render_sector[r.now.sector];
		r.sect = &doom->sectors[r.now.sector];
		/* Rendu chaque mur de ce secteur qui fait face au joueur. */
		r.i = -1;
		// pour r.i dans les bords du secteur
		while (++r.i < r.sect->pts)
		{
			ft_coord_wall(doom, &r);
			/* Le mur est-il au moins partiellement devant le joueur? */
			if (r.t1.y <= 0 && r.t2.y <= 0)
				continue;
			ft_position_wall(doom, &r);
			// Rendre seulement si c'est visible
			if (r.lim_x.x >= r.lim_x.y || r.lim_x.x > r.now.x2 || r.lim_x.y < r.now.x1)
				continue;
			ft_coord_ceil_floor(doom, &r);
			/* Rendu du mur */
			ft_render_wall(doom, &r);
		}
		++render_sector[r.now.sector];
	}
}
