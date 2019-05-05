/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 23:38:15 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 11:26:00 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	quit(t_doom *doom, char *message, int code)
{
	ft_putendl_fd(message, code > 100 ? STDERR_FILENO : STDOUT_FILENO);
	if (doom)
		megafree_1(doom);
	Mix_CloseAudio();
	SDL_Quit();
	exit(code);
}

int		quit_window(t_doom *doom, SDL_Event ev)
{
	exit_program(doom, 0);
	return (0);
}

void	exit_program(t_doom *doom, int code)
{
	if (doom && doom->win)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_WarpMouseInWindow(doom->win, WIN_W / 2, WIN_H / 2);
	}
	if (code == ERROR_GENERIC)
		quit(doom, "An error occured.", code);
	else if (code == ERROR_MEMORY)
		quit(doom, "A memory error occured.", code);
	else if (code == ERROR_MLX_INIT)
		quit(doom, "Couldn't initalize MLX.", code);
	else if (code == ERROR_MLX_WINDOW_INIT)
		quit(doom, "Couldn't initialize MLX window.", code);
	else if (code == ERROR_SDL_AUDIO_INIT)
		quit(doom, "Couldn't initialize SDL audio.", code);
	else if (code == ERROR_NOT_ENOUGH_ARGS)
		quit(doom, "Invalid arguments", code);
	else if (code == ERROR_INVALID_MAP)
		quit(doom, "Wrong map format or missing map.", code);
	else if (code == ERROR_INVALID_MUSIC)
		quit(doom, "Invalid or missing music(s)", code);
	else if (code == ERROR_INVALID_TEXTURES)
		quit(doom, "Invalid or missing texture(s). XPM files only", code);
	else if (code == ERROR_MAP_MISSING_TEXTURES)
		quit(doom, "This map is missing textures.", code);
	else if (code == ERROR_READING_FILE)
		quit(doom, "There was an error while reading your map.", code);
	else if (code == ERROR_EDITOR_NEED_MAP)
		quit(doom, "Please add a map to edit ./doom editor <map>", code);
	else if (code == ERROR_USAGE)
		quit(doom, "Usage : ./doom <map name> OR ./doom editor <map name>", code);
	else
		quit(doom, "Exiting Le Doom", code);
}
