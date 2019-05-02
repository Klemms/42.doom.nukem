/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 23:15:27 by cababou           #+#    #+#             */
/*   Updated: 2019/05/02 06:34:59 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

char	*tool_name(int tool)
{
	if (tool == tool_block)
		return ("Block");
	return ("none");
}

void	tool_button_color(t_doom *doom, int tool)
{
	doom->editor.tool_none->background_color = tool == tool_none ?
		make_rgb(150, 150, 115, 255) : make_rgb(145, 145, 145, 255);
	doom->editor.tool_block->background_color = tool == tool_block ?
		make_rgb(150, 150, 115, 255) : make_rgb(145, 145, 145, 255);
}

void	switch_tool(t_doom *doom, int to_tool)
{
	doom->editor.selected_block = NULL;
	doom->editor.hand_tool = to_tool > 0 && to_tool <= 1 ? to_tool : 0;
	free(doom->editor.current_tool->text);
	doom->editor.current_tool->text = ft_strjoin("Current tool : ", tool_name(to_tool), 0);
	text_prepare(doom, doom->editor.current_tool, 1);
	tool_button_color(doom, to_tool);
}
