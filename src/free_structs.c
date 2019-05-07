/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 20:33:22 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 10:17:05 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	megafree_1(t_doom *doom)
{
	Mix_FreeMusic(doom->musics.bgm);
	Mix_FreeChunk(doom->musics.walk);
	Mix_FreeChunk(doom->musics.shot);
}
