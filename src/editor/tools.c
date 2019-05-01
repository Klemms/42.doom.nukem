/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 23:15:27 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 23:24:44 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

char	*tool_name(int tool)
{
	if (tool == TOOL_BLOCK)
		return ("Block");
	return ("none");
}

void	switch_tool(t_doom *doom, int to_tool)
{
	doom->editor.hand_tool = to_tool > 0 && to_tool <= 1 ? to_tool : 0;
	free(doom->editor.current_tool->text);
	doom->editor.current_tool->text = ft_strjoin("Current tool : ", tool_name(to_tool), 0);
	text_prepare(doom, doom->editor.current_tool, 1);
}
