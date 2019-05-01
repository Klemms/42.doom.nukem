/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:24:22 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 03:58:44 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Uint32		get_t_exact_pixel(t_texture *texture, int x, int y)
{
	/*printf("d: %d\n", texture->surface->format->BitsPerPixel);
	printf("d: %d\n\n", texture->surface->format->BytesPerPixel);
	fflush(stdout);*/
	if (texture->surface->w < x || texture->surface->h < y)
		return (0);
	return (((Uint32 *)texture->surface->pixels)[y * texture->surface->w + x]);
}

SDL_Surface	*get_surface(t_doom *doom, int texture_id)
{
	if (texture_id >= doom->textures->lastelement->index)
		return (NULL);
	return (((t_texture *)ft_lstget_fromelement(texture_id, doom->textures->firstelement)->content)->surface);
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
		{
			tmp_texture->surface = IMG_Load(tmp_texture->texture_name);
			tmp_texture->surface = SDL_ConvertSurfaceFormat(tmp_texture->surface, doom->surface->format->format, 0);
			tmp_texture->tex_pixels = tmp_texture->surface->w * tmp_texture->surface->h;
		}
		lst = lst->next;
	}
	doom->texture_amount = lstcontainer_size(doom->textures);
}
