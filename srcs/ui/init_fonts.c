/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fonts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 04:58:41 by cababou           #+#    #+#             */
/*   Updated: 2019/04/18 06:33:01 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_fonts(t_doom *doom)
{
	if (!(doom->texts = lstcontainer_new()))
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);
	if (!(doom->fonts = lstcontainer_new()))
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);
	TTF_Init();
	lstcontainer_add(doom->fonts, TTF_OpenFont("fonts/Riffic.ttf", 100));
}

void	destroy_fonts(t_doom *doom)
{
	t_list	*tmp;

	tmp = doom->fonts->firstelement;
	while (tmp)
	{
		TTF_CloseFont(tmp->content);
		tmp = tmp->next;
	}
	ft_lstdel(doom->fonts->firstelement, 0);
	free(doom->fonts);
	TTF_Quit();
}
