/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:10:41 by cababou           #+#    #+#             */
/*   Updated: 2018/09/11 22:21:20 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list *lst, int free_content)
{
	t_list	*element;
	t_list	*next;

	if (lst == NULL)
		return ;
	element = ft_lstgetfirst(lst);
	while (element)
	{
		if (element->content && free_content)
			free(element->content);
		next = element->next;
		free(element);
		element = next;
	}
}
