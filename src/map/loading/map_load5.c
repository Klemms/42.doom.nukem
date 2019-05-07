/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:14:38 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 15:11:31 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			spritecount(t_list *sprites)
{
	size_t		count;
	t_list		*tmp;
	t_sprite	*s;

	tmp = sprites;
	count = 0;
	while (tmp)
	{
		s = tmp->content;
		if (!s->dontsave)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	read_sprite(t_doom *d, char *l, t_sprite *sprite)
{
	size_t		i;

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
	i += mgnc(l + i, ',');
	sprite->type = ft_atoi(
		ft_strsubuntil(l + i, 0, mgnc(l + i, ','), 0), 1);
	i += mgnc(l + i, ',');
	sprite->obtainable = ft_atoi(
		ft_strsubuntil(l + i, 0, mgnc(l + i, ','), 0), 1);
	//free(l);
}

void		read_sprites(t_doom *d, t_nmap *m, char *l)
{
	t_sprite	*sprite;

	if (l[0] == '[')
	{
		if (!(sprite = mmalloc(sizeof(t_sprite))))
			exit_program(d, ERROR_SDL_AFTER_INIT);
		read_sprite(d, ft_strsubuntil(l, 1, ft_strlen(l) - 1, 1), sprite);
		lstcontainer_add(m->sprites, sprite);
	}
}
