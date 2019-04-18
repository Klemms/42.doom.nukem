/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 03:51:24 by cababou           #+#    #+#             */
/*   Updated: 2019/04/18 06:30:29 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_el_ui	*create_ui_element(t_doom *doom)
{
	t_el_ui	*element;

	if (!(element = mmalloc(sizeof(t_el_ui))))
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);
	element->id = next_id(doom);
	element->pos_x = 0;
	element->pos_y = 0;
	element->width = 100;
	element->height = 100;
	return (element);
}
