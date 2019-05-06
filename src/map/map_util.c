/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:44:00 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 11:59:03 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_block_type	*make_block_type(t_doom *doom, char *bn, Uint32 bc, int bt)
{
	t_block_type	*block_type;

	if (!(block_type = mmalloc(sizeof(t_block_type))))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	block_type->block_name = ft_strdup(bn);
	block_type->block_color = bc;
	block_type->block_type = bt;
	return (block_type);
}
