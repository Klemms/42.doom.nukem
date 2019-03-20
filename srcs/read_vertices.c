/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_vertices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:24:16 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/08 16:59:57 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_xy	*ft_new_vertex(t_xy *vert, char *y, char *x)
{
	t_xy	*new;

	if (!(new = (t_xy*)malloc(sizeof(t_xy))))
		ft_quit(NULL, "Error: ft_new_vertex don't malloc", 0);
	new->x = ft_atof(x);
	new->y = ft_atof(y);
	new->next = vert;
	return (new);
}

void	ft_read_vertices(t_read *r)
{
	int	i;

	r->split = ft_strsplit(r->line, ' ');
	i = 1;
	while (r->split[++i])
	{
		r->num_vertices++;
		r->vert = ft_new_vertex(r->vert, r->split[1], r->split[i]);
	}
	ft_free_split(r->split);
}

void	ft_tab_vertices(t_read *r)
{
	int		i;
	t_xy	*v;

	i = r->num_vertices;
	if (!(r->vertices = (t_xy*)malloc(sizeof(t_xy) * i)))
		ft_quit(NULL, "Error: ft_tab_vertices don't malloc", 0);
	while (--i >= 0)
	{
		v = r->vert;
		r->vertices[i] = *r->vert;
		r->vertices[i].next = NULL;
		r->vert = r->vert->next;
		free(v);
	}
}
