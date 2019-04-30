/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:24:22 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 20:24:19 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface	*get_surface(t_doom *doom, int texture_id)
{
	return (((t_texture *)ft_lstget(texture_id, doom->textures->firstelement)->content)->surface);
}

t_texture	*make_texture(t_doom *doom, SDL_Surface *surface, char *texture_name)
{
	t_texture	*texture;

	if (!(texture = mmalloc(sizeof(t_texture))))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	texture->surface = surface;
	texture->texture_name = texture_name;
	return (texture);
}

void		init_textures(t_doom *doom)
{
	t_list		*lst;
	t_texture	*tmp_texture;

	lst = doom->textures->firstelement;
	while (lst)
	{
		tmp_texture = (t_texture *)lst->content;
		if (!tmp_texture->surface)
			tmp_texture->surface = IMG_Load(tmp_texture->texture_name);
		lst = lst->next;
	}
}
