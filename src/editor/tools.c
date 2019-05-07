/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 23:15:27 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 06:16:36 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

char	*tool_name(int tool)
{
	if (tool == tool_block)
		return ("Block");
	if (tool == tool_textures)
		return ("Texture Picker");
	return ("none");
}

void	tool_button_color(t_doom *doom, int tool)
{
	doom->editor.tool_none->background_color = tool == tool_none ?
		doom->editor.select_color : doom->editor.base_color;
	doom->editor.tool_block->background_color = tool == tool_block ?
		doom->editor.select_color : doom->editor.base_color;
}

void	switch_tool(t_doom *doom, int to_tool, t_block_type *block)
{
	if (to_tool != tool_textures)
		doom->editor.selected_block = block;
	doom->editor.hand_tool = to_tool > 0 && to_tool <= 2 ? to_tool : 0;
	free(doom->editor.current_tool->text);
	doom->editor.current_tool->text = ft_strjoin("Current tool : ", tool_name(to_tool), 0);
	text_prepare(doom, doom->editor.current_tool, 1, 0);
	tool_button_color(doom, to_tool);
}
