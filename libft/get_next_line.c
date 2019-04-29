/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:50:57 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 12:29:55 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*get_element_by_fd(t_lstcontainer *files, int fd)
{
	t_list	*item;
	t_file	*file;

	item = files->firstelement;
	while (item)
	{
		file = (t_file *)item->content;
		if (file->file_descriptor == fd)
			return (item);
		item = item->next;
	}
	if ((file = mmalloc(sizeof(t_file *))) == NULL)
		return (NULL);
	file->content = ft_strnew(0);
	file->file_descriptor = fd;
	file->end = 0;
	files->add(files, file);
	return (ft_lstgetlast(files->firstelement));
}

int		has_line(t_file *file)
{
	size_t	i;
	int		content_size;

	i = 0;
	content_size = ft_strlen(file->content);
	while (file->content[i])
	{
		if (file->content[i] == '\n')
			return (i);
		i++;
	}
	return (file->end == 1 && content_size != 0 ? content_size : -1);
}

void	read_until_next_line(t_file *current_file)
{
	int		read_size;
	char	*buffer;

	buffer = ft_strnew(BUFF_SIZE);
	while (has_line(current_file) < 0
	&& (read_size = read(current_file->file_descriptor, buffer, BUFF_SIZE)) > 0)
	{
		buffer[read_size] = '\0';
		current_file->content = ft_strjoin(current_file->content, buffer, 1);
	}
	ffree(buffer);
	if (read_size == 0)
		current_file->end = 1;
	if (read_size == -1)
		current_file->end = -1;
}

char	*get_line(t_file *current_file)
{
	int		l_position;
	char	*return_string;

	if ((l_position = has_line(current_file)) >= 0)
	{
		return_string = ft_strsub(current_file->content, 0, l_position, 0);
		current_file->content = ft_strsub(current_file->content, l_position + 1,
						ft_strlen(current_file->content) - l_position, 1);
		return (return_string);
	}
	else
	{
		read_until_next_line(current_file);
		if (current_file->end == 0
			|| (current_file->end == 1
			&& ft_strlen(current_file->content) != 0))
			return (get_line(current_file));
	}
	return (NULL);
}

int		get_next_line(const int fd, char **line)
{
	static t_lstcontainer	*files;
	t_list					*current_element;
	char					*read_line;

	if (files == NULL)
		files = lstcontainer_new();
	if (fd < 0)
		return (-1);
	current_element = get_element_by_fd(files, fd);
	read_line = get_line((t_file *)current_element->content);
	if (read_line == NULL)
		if (((t_file *)current_element->content)->end == -1
			|| ((t_file *)current_element->content)->end == 1)
		{
			ffree(((t_file *)current_element->content)->content);
			files->remove(files, current_element);
			return (((t_file *)current_element->content)->end == -1 ? -1 : 0);
		}
	*line = read_line;
	return (1);
}
