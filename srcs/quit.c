/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:54:21 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/07 17:30:04 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_quit(t_doom *doom, const char *message, int error)
{
	if (error >= 2)
	{
		SDL_DestroyRenderer(doom->rend);
		SDL_DestroyWindow(doom->win);
	}
	if (error >= 1)
	{
		SDL_Log("Error: %s > %s\n", message, SDL_GetError());
		SDL_Quit();
	}
	if (error == 0)
		ft_putendl(message);
	exit(EXIT_FAILURE);
}
