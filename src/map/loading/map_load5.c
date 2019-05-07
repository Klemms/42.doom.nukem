/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:14:38 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 20:53:28 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sprite	*make_doorwindowsprite(t_doom *d, t_mblock *b)
{
	t_sprite	*sprite;

	if (!(sprite = mmalloc(sizeof(t_sprite))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	sprite->dontsave = 1;
	sprite->pos.x = b->x;
	sprite->pos.y = b->y;
	sprite->texture = b->n_texture;
	sprite->texture_back = b->s_texture;
	sprite->render_mode = b->block_type == block_door ? rend_door : rend_window;
	return (sprite);
}

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

void		read_sprite2(t_doom *d, char *l, t_sprite *sprite, size_t *i)
{
	(void)d;
	sprite->type = ft_atoi(
		ft_strsubuntil(l + *i, 0, mgnc(l + *i, ','), 0), 1);
	*i = *i + mgnc(l + *i, ',');
	sprite->obtainable = ft_atoi(
		ft_strsubuntil(l + *i, 0, mgnc(l + *i, ','), 0), 1);
}

void		read_sprite(t_doom *d, char *l, t_sprite *sprite)
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
	read_sprite2(d, l, sprite, &i);
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
