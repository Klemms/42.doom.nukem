/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:57:55 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/12 13:50:07 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	ft_read_player(t_doom *doom, t_read *r)
{
	ft_tab_sectors(doom, r);
	r->split = ft_strsplit(r->line, ' ');
	doom->player = (t_player) {{ft_atof(r->split[1]),
	ft_atof(r->split[2]), 0}, {0, 0, 0}, ft_atof(r->split[3]),
		0, 0, 0, ft_atoi(r->split[4])};
	ft_free_split(r->split);
	doom->player.where.z = doom->sectors[doom->player.sector].floor + CAM_H;
}

void	ft_read_map(int fd, t_doom *doom)
{
	t_read	read;

	read.vert = NULL;
	read.vertices = NULL;
	read.sect = NULL;
	read.num_vertices = 0;
	while (get_next_line(fd, &read.line))
	{
		if (read.line[0] == 'v')
			ft_read_vertices(&read);
		else if (read.line[0] == 's')
			ft_read_sectors(doom, &read);
		else if (read.line[0] == 'p')
			ft_read_player(doom, &read);
		free(read.line);
	}
	free(read.line);
	free(read.vertices);
	close(fd);
}
