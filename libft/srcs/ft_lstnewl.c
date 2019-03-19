/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:00:03 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/28 15:57:13 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnewl(void *content, size_t content_size, t_list *first)
{
	t_list	*last;
	t_list	*new;

	last = first;
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		new->content = content;
		new->content_size = content_size;
	}
	else
		return (NULL);
	new->next = NULL;
	if (first)
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		first = new;
	return (first);
}
