/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 02:29:43 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 02:34:56 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	editor_init_map(t_doom *doom)
{
	SDL_SetWindowTitle(doom->win, ft_strjoin("Le Doom - Editing : ", doom->map.map_name, 0));
}
