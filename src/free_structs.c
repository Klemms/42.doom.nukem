/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 20:33:22 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 14:19:08 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_textures(t_wolf *w)
{
	if (w->texture[0].img.ptr)
	{
		mlx_destroy_image(w->mlx, w->texture[0].img.ptr);
	}
	if (w->texture[1].img.ptr)
	{
		mlx_destroy_image(w->mlx, w->texture[1].img.ptr);
	}
	if (w->texture[2].img.ptr)
	{
		mlx_destroy_image(w->mlx, w->texture[2].img.ptr);
	}
	if (w->texture[3].img.ptr)
	{
		mlx_destroy_image(w->mlx, w->texture[3].img.ptr);
	}
}

void	free_player(t_wolf *w)
{
	ffree(w->you->pos);
	ffree(w->you->dir);
	ffree(w->you->plane);
	ffree(w->you);
}

void	free_map(t_wolf *w)
{
	int		i;

	i = 0;
	if (w->map->m)
	{
		while (i < w->map->height)
		{
			ffree(w->map->m[i]);
			i++;
		}
		ffree(w->map->m);
	}
	ffree(w->map);
}

void	free_sight(t_wolf *w)
{
	if (w->sight->pos)
		ffree(w->sight->pos);
	ffree(w->sight);
}

void	megafree_1(t_wolf *w)
{
	if (w->textures && w->textures->firstelement)
		ft_lstdel(w->textures->firstelement, 1);
	ffree(w->textures);
	free_textures(w);
	ffree(w->keys);
	w->keys = NULL;
	if (w->you)
		free_player(w);
	free_map(w);
	if (w->mlx && w->image && w->image->ptr)
		mlx_destroy_image(w->mlx, w->image->ptr);
	ffree(w->image);
	if (w->mlx && w->window)
		mlx_destroy_window(w->mlx, w->window);
	free_sight(w);
	if (w->mlx)
		mlx_del(w->mlx);
	ffree(w);
}
