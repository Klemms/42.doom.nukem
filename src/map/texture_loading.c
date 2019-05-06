/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:24:22 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 07:29:50 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Uint32		get_t_exact_pixel(t_texture *texture, int x, int y)
{
	if (texture->surface->w < x || texture->surface->h < y)
		return (0);
	return (((Uint32 *)texture->surface->pixels)[y * texture->surface->w + x]);
}

SDL_Surface	*get_surface(t_doom *doom, int texture_id)
{
	if (texture_id > doom->nmap->textures->lastelement->index)
		return (NULL);
	return (((t_texture *)ft_lstget_fromelement(texture_id,
				doom->nmap->textures->firstelement)->content)->surface);
}

t_texture	*make_texture(t_doom *doom, SDL_Surface *surface, char *tn)
{
	t_texture	*texture;

	if (!(texture = mmalloc(sizeof(t_texture))))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	texture->surface = surface;
	texture->texture_name = tn;
	return (texture);
}

void		init_textures(t_doom *doom)
{
	t_list		*lst;
	t_texture	*tmp_texture;
	SDL_Surface	*tmp_s;

	lst = doom->nmap->textures->firstelement;
	while (lst)
	{
		tmp_texture = (t_texture *)lst->content;
		if (!tmp_texture->surface)
		{
			tmp_texture->surface = IMG_Load(tmp_texture->texture_name);
			tmp_s = tmp_texture->surface;
			tmp_texture->surface = SDL_ConvertSurfaceFormat(
				tmp_texture->surface, doom->surface->format->format, 0);
			SDL_FreeSurface(tmp_s);
			tmp_texture->tex_pixels = tmp_texture->surface->w
				* tmp_texture->surface->h;
		}
		lst = lst->next;
	}
	doom->texture_amount = lstcontainer_size(doom->nmap->textures);
}

t_texture	*load_texture(char *path, t_doom *doom)
{
	t_texture	*texture;

	if (!(texture = mmalloc(sizeof(t_texture))))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	texture->surface = IMG_Load(path);
	texture->surface = SDL_ConvertSurfaceFormat(texture->surface,
		SDL_PIXELFORMAT_ARGB32, 0);
	texture->tex_pixels = texture->surface->w * texture->surface->h;
	return (texture);
}
