/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:04:31 by cababou           #+#    #+#             */
/*   Updated: 2019/03/22 06:34:38 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_el_button	*create_button(t_doom *doom)
{
	t_el_button	*but;

	if (!(but = malloc(sizeof(t_el_button))))
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);
	return (but);
}
