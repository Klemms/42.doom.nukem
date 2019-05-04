/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 03:08:26 by cababou           #+#    #+#             */
/*   Updated: 2019/05/04 08:59:48 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <fcntl.h>
#include <errno.h>

int		read_map(char *path)
{
	int		fd;
	int		sr;
	void	*buff;
	void	*test;
	size_t	sdata;

	//test = mmalloc(sizeof(char) * 1025);
	fd = open("maps/test.nmap", O_RDONLY);
	if (fd < 0)
		return (errno);
	sr = 0;
	sdata = 0;
	buff = ft_strnew(BUFF_SIZE);
	while ((sr = read(fd, buff, BUFF_SIZE)) > 0)
	{
		printf("sdata : %d\n", sr);
		test = ft_memjoin(&test, &buff, sdata, sr);
		sdata += sr;
	}
		printf("err : %s\n", strerror(errno));
	//printf("%d %d %d\n", ((char *)test)[0], ((char *)test)[4], ((SDL_Color *)((char *)test)[8])->r);
	fflush(stdout);
	close(fd);
		printf("FINISH READING");
	return (0);
}

void	write_textures(t_nmap *m, int fd)
{
	t_list		*tmp;
	t_texture	*tmp_texture;
	int			sz;
	size_t		x;

	tmp = m->textures->firstelement;
	sz = lstcontainer_size(m->textures);
	write(fd, &sz, sizeof(int));
	while (tmp)
	{
		tmp_texture = (t_texture *)tmp->content;
		x = 0;
		write(fd, &tmp_texture->tex_pixels, sizeof(int));
		ft_putnbr(x);
		ft_putendl(" TEXT");
		while (x < tmp_texture->tex_pixels)
		{
			write(fd, &(((int *)tmp_texture->surface->pixels)[x]), sizeof(int));
			x++;
		}
		tmp = tmp->next;
	}
}

int		write_map(t_nmap *m, char *path)
{
	int		fd;
	size_t	sizewrt;
	size_t	x;
	size_t	y;

	fd = open("maps/test.nmap", O_WRONLY | O_CREAT);
	if (fd < 0)
		return (errno);

	write(fd, &m->size_x, sizeof(int));
	write(fd, &m->size_y, sizeof(int));
	write(fd, &m->skybox_color, sizeof(SDL_Color));
	write(fd, &m->size_x, sizeof(SDL_Color)); // On ajoute d'autres ints inutilises
	write(fd, &m->size_x, sizeof(SDL_Color)); // pour avoir de la place dans le futur
	write(fd, &m->size_x, sizeof(SDL_Color));
	write(fd, &m->size_x, sizeof(SDL_Color));
	write(fd, &m->size_x, sizeof(SDL_Color));

	x = 0;
	while (x < m->size_x)
	{
		y = 0;
		while (y < m->size_y)
		{
			write(fd, &m->map[x][y].block_type, sizeof(int));
			write(fd, &m->map[x][y].orientation, sizeof(int));
			write(fd, &m->map[x][y].x_size, sizeof(int));
			write(fd, &m->map[x][y].y_size, sizeof(int));
			write(fd, &m->map[x][y].height, sizeof(int));
			write(fd, &m->map[x][y].ceiling_height, sizeof(int));
			write(fd, &m->map[x][y].has_ceiling, sizeof(int));
			write(fd, &m->map[x][y].ceilng_tex, sizeof(int));
			write(fd, &m->map[x][y].floor_tex, sizeof(int));
			write(fd, &m->map[x][y].n_texture, sizeof(int));
			write(fd, &m->map[x][y].s_texture, sizeof(int));
			write(fd, &m->map[x][y].w_texture, sizeof(int));
			write(fd, &m->map[x][y].e_texture, sizeof(int));
			write(fd, &m->map[x][y].light, sizeof(int));
			write(fd, &m->map[x][y].collides, sizeof(int));
			write(fd, &m->map[x][y].block_type, sizeof(int));
			write(fd, &m->map[x][y].block_type, sizeof(int));
			write(fd, &m->map[x][y].block_type, sizeof(int));
			write(fd, &m->map[x][y].block_type, sizeof(int));
			write(fd, &m->map[x][y].block_type, sizeof(int));
			write(fd, &m->map[x][y].block_type, sizeof(int));
			y++;
		}
		x++;
	}
	write_textures(m, fd);


	fflush(stdout);
	close(fd);
	return (0);
}
