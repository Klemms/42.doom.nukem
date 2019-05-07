/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 03:32:55 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 20:52:20 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <sys/stat.h>

void	write_intdl(int fd, int i, int comma, int endl)
{
	char	*s;

	s = ft_itoa(i);
	ft_putstr_fd(s, fd);
	if (comma)
		ft_putchar_fd(',', fd);
	if (endl)
		ft_putchar_fd('\n', fd);
	free(s);
}

void	wrt_mapheader(int fd, t_nmap *m)
{
	ft_putchar_fd('[', fd);
	write_intdl(fd, m->size_x, 1, 0);
	write_intdl(fd, m->size_y, 1, 0);
	write_intdl(fd, m->skybox_color.r, 1, 0);
	write_intdl(fd, m->skybox_color.g, 1, 0);
	write_intdl(fd, m->skybox_color.b, 1, 0);
	write_intdl(fd, m->skybox_color.a, 0, 0);
	write(fd, "]\n", 2);
}

void	wrt_mapdata(int fd, t_nmap *m, int x, int y)
{
	ft_putchar_fd('[', fd);
	write_intdl(fd, m->map[y][x].block_type, 1, 0);
	write_intdl(fd, m->map[y][x].orientation, 1, 0);
	write_intdl(fd, m->map[y][x].x_size, 1, 0);
	write_intdl(fd, m->map[y][x].y_size, 1, 0);
	write_intdl(fd, m->map[y][x].event_id, 1, 0);
	write_intdl(fd, m->map[y][x].ceiling_height, 1, 0);
	write_intdl(fd, m->map[y][x].has_ceiling, 1, 0);
	write_intdl(fd, m->map[y][x].ceilng_tex, 1, 0);
	write_intdl(fd, m->map[y][x].floor_tex, 1, 0);
	write_intdl(fd, m->map[y][x].n_texture, 1, 0);
	write_intdl(fd, m->map[y][x].s_texture, 1, 0);
	write_intdl(fd, m->map[y][x].w_texture, 1, 0);
	write_intdl(fd, m->map[y][x].e_texture, 1, 0);
	write_intdl(fd, m->map[y][x].light, 1, 0);
	write_intdl(fd, m->map[y][x].collides, 0, 0);
	write(fd, "]\n", 1 + (x == m->size_x - 1));
}

int		write_map(t_nmap *m, char *path)
{
	int		fd;
	size_t	x;
	size_t	y;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_NOFOLLOW);
	if (fd < 0)
		return (1);
	wrt_mapheader(fd, m);
	y = 0;
	while (y < (size_t)m->size_y)
	{
		x = 0;
		while (x < (size_t)m->size_x)
		{
			wrt_mapdata(fd, m, x, y);
			x++;
		}
		y++;
	}
	wrt_textures(m, fd);
	wrt_sprites(m, fd);
	chmod(path, S_IRWXU);
	close(fd);
	return (0);
}
