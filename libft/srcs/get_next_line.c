/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:27:25 by lde-batz          #+#    #+#             */
/*   Updated: 2018/12/12 15:59:17 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_text	*ft_lstnew_txt(const int fd, t_text *repertoire)
{
	t_text *tmp;

	if (!(tmp = (t_text*)malloc(sizeof(t_text))))
		return (NULL);
	if (!(tmp->txt = ft_strnew(0)))
		return (NULL);
	tmp->txt_fd = fd;
	tmp->next = repertoire;
	return (tmp);
}

int		ft_putrdintxt(char **txtrd, const int fd)
{
	int		ret;
	char	*buf;

	ret = 1;
	buf = ft_strnew(BUFF_SIZE + 1);
	while (!(ft_strchr(*(txtrd), '\n')) && ret != 0)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		*txtrd = ft_strjoin(*txtrd, buf, 1);
		if (ret < BUFF_SIZE && ret > 0)
		{
			if (buf[ret - 1] == '\n')
			{
				buf[0] = '\n';
				buf[1] = '\0';
				*txtrd = ft_strjoin(*txtrd, buf, 1);
			}
		}
	}
	free(buf);
	return (1);
}

int		ft_putinline(char **txtrd, char **line)
{
	int	ret;

	ret = 0;
	while ((*txtrd)[ret] != '\n' && (*txtrd)[ret] != '\0')
		ret++;
	*line = ft_strsub(*txtrd, 0, ret, 0);
	if ((*txtrd)[0] == '\0')
	{
		free(*txtrd);
		return (0);
	}
	if ((*txtrd)[ret] == '\0')
		ret--;
	*txtrd = ft_strsub(*txtrd, ret + 1, ft_strlen(*txtrd) - (ret + 1), 1);
	return (1);
}

void	ft_free_link(t_text *rep, t_text *lst)
{
	t_text	*before;

	before = rep;
	if (before == lst)
		rep = rep->next;
	else
	{
		while (before->next != lst)
			before = before->next;
		before->next = lst->next;
	}
	free(lst);
}

int		get_next_line(const int fd, char **line)
{
	static t_text	*repertoire = NULL;
	t_text			*lst;

	if (fd < 0)
		return (-1);
	lst = repertoire;
	while (lst && lst->txt_fd != fd)
		lst = lst->next;
	if (!lst)
	{
		if ((repertoire = ft_lstnew_txt(fd, repertoire)) == NULL)
			return (-1);
		lst = repertoire;
	}
	if (ft_putrdintxt(&(lst->txt), fd) == -1)
		return (-1);
	if (ft_putinline(&(lst->txt), line) == 1)
		return (1);
	else
	{
		ft_free_link(repertoire, lst);
		return (0);
	}
}
