/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 23:38:15 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 14:17:13 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

int		close_window(t_wolf *w)
{
	exit_program(w, 0);
	return (0);
}

void	quit(t_wolf *w, char *message, int code)
{
	ft_putendl(message);
	if (w)
		megafree_1(w);
	exit(code);
}

void	exit_program(t_wolf *w, int code)
{
	if (code == ERROR_GENERIC)
		quit(w, "An error occured.", code);
	else if (code == ERROR_MEMORY)
		quit(w, "A memory error occured.", code);
	else if (code == ERROR_MLX_INIT)
		quit(w, "Couldn't initalize MLX.", code);
	else if (code == ERROR_MLX_WINDOW_INIT)
		quit(w, "Couldn't initialize MLX window.", code);
	else if (code == ERROR_NOT_ENOUGH_ARGS)
		quit(w, "Invalid arguments", code);
	else if (code == ERROR_INVALID_MAP)
		quit(w, "Wrong map format or missing map.", code);
	else if (code == ERROR_INVALID_TEXTURES)
		quit(w, "Invalid or missing texture(s). XPM files only", code);
	else if (code == ERROR_MAP_MISSING_TEXTURES)
		quit(w, "This map is missing textures.", code);
	else if (code == ERROR_READING_FILE)
		quit(w, "There was an error while reading your map.", code);
	else
		quit(w, "Exiting Wolf3D", code);
}
