/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:44:00 by cababou           #+#    #+#             */
/*   Updated: 2019/05/02 00:59:20 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		char_to_blocktype(char block)
{
	if (block == '.')
		return (block_air);
	else if (block == '#')
		return (block_wall);
	else if (block == 'T')
		return (block_small_wall);
	else if (block == 'C')
		return (block_wall);
	else
		return (block_wall);
}
