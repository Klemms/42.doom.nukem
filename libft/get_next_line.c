/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 03:19:27 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 06:35:02 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*get_file(t_lstcontainer *fds, int fd)
{
	t_list	*tmp;
	t_file	*tmp_file;

	tmp = fds->firstelement;
	while (tmp)
	{
		tmp_file = (t_file *)tmp->content;
		if (tmp_file->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp_file = mmalloc(sizeof(t_file))))
		return (NULL);
	tmp_file->fd = fd;
	tmp_file->state = 1;
	tmp_file->line = ft_strnew(0, 0);
	lstcontainer_add(fds, tmp_file);
	return (fds->lastelement);
}

void	cat_lines(t_file *file, t_lstcontainer *lines, size_t sz)
{
	t_list	*tmp;
	char	*s;
	size_t	m_sz;

	s = ft_strnew(ft_strlen(file->line) + sz, 0);
	ft_strcpy(s, file->line);
	m_sz = ft_strlen(file->line);
	tmp = lines->firstelement;
	while (tmp)
	{
		ft_strcpy(s + m_sz, tmp->content);
		m_sz += ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	ft_lstdel(lines->firstelement, 1);
	free(file->line);
	file->line = NULL;
	file->line = s;
}

void	c_read(t_file *file)
{
	char			*buff;
	t_lstcontainer	*lines;
	size_t			sz;
	int				rd;

	buff = ft_strnew(BUFF_SIZE, 0);
	lines = lstcontainer_new();
	sz = 0;
	while ((rd = read(file->fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rd] = '\0';
		lstcontainer_add(lines, ft_strdup(buff));
		sz += rd;
		if (ft_getnextchar(buff, '\n') != -1)
			break ;
	}
	file->state = rd;
	cat_lines(file, lines, sz);
	free(lines);
	free(buff);
}

char	*next_line(t_file *file)
{
	char	*s;
	int		sz;

	if (!file->line)
		return (NULL);
	sz = ft_getnextchar(file->line, '\n') - 1;
	s = ft_strsubuntil(file->line, 0, sz, 0);
	file->line = ft_strsubuntil(file->line, sz + 1, ft_strlen(file->line), 1);
	return (s);
}

int		get_next_line(int fd, char **line)
{
	static t_lstcontainer	*fds = NULL;
	t_list					*lfile;
	t_file					*file;

	fds = fds == NULL ? lstcontainer_new() : fds;
	if (fd < 0 || !(lfile = get_file(fds, fd)))
		return (-1);
	file = lfile->content;
	if (file->line && ft_getnextchar(file->line, '\n') == -1
		&& file->state > 0)
		c_read(file);
	if (file->state < 0)
	{
		free(file->line);
		lstcontainer_remove(fds, lfile);
		return (-1);
	}
	*line = next_line(file);
	if (file->state == 0)
	{
		free(file->line);
		lstcontainer_remove(fds, lfile);
		return (0);
	}
	return (1);
}
