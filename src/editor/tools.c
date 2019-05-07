/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 23:15:27 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 22:50:07 by cababou          ###   ########.fr       */
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
	if (tool == tool_sprite)
		return ("Sprite");
	return ("none");
}

void	tool_button_color(t_doom *doom, int tool)
{
	doom->editor.tool_none->background_color = tool == tool_none ?
		doom->editor.select_color : doom->editor.base_color;
	doom->editor.tool_block->background_color = tool == tool_block ?
		doom->editor.select_color : doom->editor.base_color;
	doom->editor.tool_sprite->background_color = tool == tool_sprite ?
		doom->editor.select_color : doom->editor.base_color;
}

void	switch_tool_sprite(t_doom *doom, int to_tool, t_sprite_type *sp)
{
	if (to_tool != tool_textures)
		doom->editor.selected_sprite = sp;
	doom->editor.selected_block = NULL;
	doom->editor.hand_tool = to_tool > 0 && to_tool <= 3 ? to_tool : 0;
	free(doom->editor.current_tool->text);
	doom->editor.current_tool->text
		= ft_strjoin("Current tool : ", tool_name(to_tool), 0);
	if (doom->editor.current_tool)
	{
		text_prepare(doom, doom->editor.current_tool, 1, 0);
	}
	tool_button_color(doom, to_tool);
}

void	switch_tool(t_doom *doom, int to_tool, t_block_type *block)
{
	if (to_tool != tool_textures)
		doom->editor.selected_block = block;
	if (to_tool != tool_textures)
		doom->editor.selected_sprite = NULL;
	doom->editor.hand_tool = to_tool > 0 && to_tool <= 3 ? to_tool : 0;
	if (doom->editor.current_tool)
	{
		free(doom->editor.current_tool->text);
		doom->editor.current_tool->text = ft_strjoin("Current tool : ",
														tool_name(to_tool), 0);
		text_prepare(doom, doom->editor.current_tool, 1, 0);
	}
	tool_button_color(doom, to_tool);
}
