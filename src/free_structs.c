/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 20:33:22 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 05:08:31 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	megafree_1(t_doom *doom)
{
	Mix_FreeMusic(doom->scores.bgm);
	Mix_FreeChunk(doom->scores.walk);
	Mix_FreeChunk(doom->scores.shot);
}
