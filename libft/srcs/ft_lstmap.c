/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:44:26 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/14 18:14:27 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*modiflst;
	t_list	*newlst;
	t_list	*res;

	if (!lst || !f)
		return (NULL);
	modiflst = f(lst);
	res = ft_lstnew(modiflst->content, modiflst->content_size);
	if (res)
	{
		newlst = res;
		lst = lst->next;
		while (lst)
		{
			modiflst = f(lst);
			newlst->next = ft_lstnew(modiflst->content, modiflst->content_size);
			if (!newlst)
				return (NULL);
			newlst = newlst->next;
			lst = lst->next;
		}
	}
	return (res);
}
