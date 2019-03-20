/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:23:05 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/19 12:07:31 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sector	*ft_new_sector(t_sector *sect, char *ground, char *ceil)
{
	t_sector	*new;

	if (!(new = (t_sector*)malloc(sizeof(t_sector))))
		ft_quit(NULL, "Error: ft_new_sector don't malloc", 0);
	new->floor = ft_atof(ground);
	new->ceil = ft_atof(ceil);
	new->pts = 0;
	new->next = sect;
	return (new);
}

void		ft_vertex_of_sector(t_read *r)
{
	int	i;

	i = 2;
	while (r->split[++i][0] != 'x')
		r->sect->vertex[i - 3] = r->vertices[ft_atoi(r->split[i])];
}

void		ft_read_sectors(t_doom *doom, t_read *r)
{
	int	i;
	int	tab[128];

	if (r->vertices == NULL)
		ft_tab_vertices(r);
	doom->num_sectors++;
	r->split = ft_strsplit(r->line, ' ');
	r->sect = ft_new_sector(r->sect, r->split[1], r->split[2]);
	i = 2;
	while (r->split[++i])
		tab[i - 3] = ft_atoi(r->split[i]);
	r->sect->pts = (i - 3) / 2;
	if (!(r->sect->vertex = (t_xy*)malloc(sizeof(t_xy) * (r->sect->pts + 1))))
		ft_quit(NULL, "Error: ft_read_sector: vertex don't malloc", 0);
	if (!(r->sect->neighbors = (signed char*)malloc(sizeof(signed char) *
			r->sect->pts)))
		ft_quit(NULL, "Error: ft_read_sector: neighbors don't malloc", 0);
	i = -1;
	while (++i < r->sect->pts)
		r->sect->vertex[i + 1] = r->vertices[tab[i]];
	r->sect->vertex[0] = r->sect->vertex[i];
	i = -1;
	while (++i < r->sect->pts)
		r->sect->neighbors[i] = tab[i + r->sect->pts];
	ft_free_split(r->split);
}

void		ft_tab_sectors(t_doom *doom, t_read *r)
{
	int			i;
	t_sector	*s;

	i = doom->num_sectors;
	if (!(doom->sectors = (t_sector*)malloc(sizeof(t_sector) * i)))
		ft_quit(NULL, "Error: ft_tab_sectors don't malloc", 0);
	while (--i >= 0)
	{
		s = r->sect;
		doom->sectors[i] = *s;
		doom->sectors[i].next = NULL;
		r->sect = r->sect->next;
		free(s);
	}
}
