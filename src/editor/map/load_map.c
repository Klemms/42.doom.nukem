/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 02:29:43 by cababou           #+#    #+#             */
/*   Updated: 2019/05/04 01:07:43 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	editor_init_map(t_doom *doom)
{
	char	*s;

	if (!(s = ft_strjoin("Le Doom - Editing : ", doom->nmap->map_name, 2)))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	SDL_SetWindowTitle(doom->win, s);
	free(s);
}
