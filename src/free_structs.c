/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 20:33:22 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 14:25:22 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_textures(t_doom *doom)
{
	if (doom->texture[0].ptr)
		mlx_destroy_image(doom->mlx, doom->texture[0].ptr);
	if (doom->texture[1].ptr)
		mlx_destroy_image(doom->mlx, doom->texture[1].ptr);
	if (doom->texture[2].ptr)
		mlx_destroy_image(doom->mlx, doom->texture[2].ptr);
	if (doom->texture[3].ptr)
		mlx_destroy_image(doom->mlx, doom->texture[3].ptr);
}

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
	if (doom->textures && doom->textures->firstelement)
		ft_lstdel(doom->textures->firstelement, 1);
	ffree(doom->textures);
	free_textures(doom);
	free_map(doom);
	if (doom->mlx && doom->img.ptr)
		mlx_destroy_image(doom->mlx, doom->img.ptr);
	if (doom->mlx && doom->window)
		mlx_destroy_window(doom->mlx, doom->window);
	if (doom->mlx)
		mlx_del(doom->mlx);
}
