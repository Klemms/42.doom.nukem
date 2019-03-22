/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:04:58 by cababou           #+#    #+#             */
/*   Updated: 2019/03/22 03:52:40 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "doom.h"

# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define MIDDLE_CLICK 3

# define KEY_PRESS 101
# define KEY_RELEASE 102

# define UI_DISABLED 201
# define UI_ENABLED 202
# define UI_HOVERED 203
# define UI_USED 204

typedef struct	s_ui_element
{
	int			id;
	int			el_state;
}				t_el_ui;


typedef struct	s_button_element
{
	t_el_ui		*ui_element;
	int			(*ui_callback)(int click_type, int x_pos, int y_pos);
	int			background_color;
	int			background_color_disabled;
	char		*text;
}				t_el_button;


#endif