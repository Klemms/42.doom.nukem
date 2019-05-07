/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:14:38 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 09:29:29 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sprite	*read_sprite(t_doom *d, char *l)
{
	t_sprite	*sprite;
	size_t		i;

	if (!(sprite = mmalloc(sizeof(t_sprite))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	i = 0;
	sprite->texture = ft_atoi(
		ft_strsubuntil(l + i, 0, mgnc(l + i, ','), 0), 1);
	i += mgnc(l + i, ',');
	sprite->texture_back = ft_atoi(
		ft_strsubuntil(l + i, 0, mgnc(l + i, ','), 0), 1);
	i += mgnc(l + i, ',');
	sprite->render_mode = ft_atoi(
		ft_strsubuntil(l + i, 0, mgnc(l + i, ','), 0), 1);
	i += mgnc(l + i, ',');
	sprite->base_x = ft_atoi(
		ft_strsubuntil(l + i, 0, mgnc(l + i, ','), 0), 1);
	i += mgnc(l + i, ',');
	sprite->base_y = ft_atoi(
		ft_strsubuntil(l + i, 0, mgnc(l + i, ','), 0), 1);
	i += mgnc(l + i, ',');
	sprite->collides = ft_atoi(
		ft_strsubuntil(l + i, 0, mgnc(l + i, ','), 0), 1);
	free(l);
	return (sprite);
}

void		read_sprites(t_doom *d, t_nmap *m, char *l)
{
	if (l[0] == '[')
	{
		lstcontainer_add(m->sprites,
			read_sprite(d, ft_strsubuntil(l, 1, ft_strlen(l) - 1, 1)));
	}
}
