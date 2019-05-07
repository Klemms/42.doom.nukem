/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:44:52 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 16:21:40 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_sprite_types(t_doom *doom)
{
	doom->sprite_types = lstcontainer_new();
	lstcontainer_add(doom->sprite_types
		, make_sprite_type(doom, "Ammunitions", 0xFF5d9b8b, sprite_ammo));
	lstcontainer_add(doom->sprite_types
		, make_sprite_type(doom, "Health", 0xFFf46842, sprite_health));
	lstcontainer_add(doom->sprite_types
		, make_sprite_type(doom, "Key", 0xFF6e5d9b, sprite_key));
}
