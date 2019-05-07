/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:24:22 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 06:10:40 by cababou          ###   ########.fr       */
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
	texture->tex_pixels = texture->surface->w * texture->surface->h;
	return (texture);
}

t_texture	*load_texture(t_doom *d, char *path)
{
	t_texture	*texture;

	if (!(texture = mmalloc(sizeof(t_texture))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	texture->surface = IMG_Load(path);
	printf("IMG_Load: %s\n", IMG_GetError());
	if (texture->surface)
	{
		texture->surface = SDL_ConvertSurfaceFormat(texture->surface,
			SDL_PIXELFORMAT_ARGB32, 0);
		texture->tex_pixels = texture->surface->w * texture->surface->h;
		return (texture);
	}
	free(texture);
	return (NULL);
}

int			add_texture(t_doom *d, char *tn)
{
	t_texture	*t;

	t = load_texture(d, ft_strjoin("textures/", tn, 0));
	if (t)
	{
		lstcontainer_add(d->nmap->textures, t);
		return (d->nmap->textures->lastelement->index);
	}
	free(d->editor.state->text);
	d->editor.state->text = ft_strdup("Couldn't load texture");
	text_prepare(d, d->editor.state, 1, 1);
	ft_putchar('\a');
	return (0);
}
