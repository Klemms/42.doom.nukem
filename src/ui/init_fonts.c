/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fonts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 04:58:41 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 16:16:27 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

TTF_Font	*make_font(t_doom *doom, char *font_path, int size)
{
	t_list	*tmp;
	t_font	*tmp_font;
	t_font	*font;

	tmp = doom->fonts->firstelement;
	while (tmp)
	{
		tmp_font = (t_font *)tmp->content;
		if (ft_strcmp(font_path, tmp_font->font_path) == 0
			&& size == tmp_font->size)
			return (tmp_font->font);
		tmp = tmp->next;
	}
	if (!(font = mmalloc(sizeof(t_font))))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	font->font = TTF_OpenFont(font_path, size);
	font->font_path = font_path;
	font->size = size;
	lstcontainer_add(doom->fonts, font);
	return (font->font);
}

void	init_fonts(t_doom *doom)
{
	t_font	*font;

	if (!(doom->texts = lstcontainer_new()))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	if (!(doom->fonts = lstcontainer_new()))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	TTF_Init();
	make_font(doom, FONT_RIFFIC, 20);
}

void	destroy_fonts(t_doom *doom)
{
	t_list	*tmp;
	t_font	*tmp_font;

	tmp = doom->fonts->firstelement;
	while (tmp)
	{
		tmp_font = (t_font *)tmp->content;
		TTF_CloseFont(tmp_font->font);
		tmp = tmp->next;
	}
	ft_lstdel(doom->fonts->firstelement, 0);
	free(doom->fonts);
	TTF_Quit();
}
