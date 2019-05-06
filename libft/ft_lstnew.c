/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 20:10:57 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 10:10:04 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list		*liste;

	if (!(liste = mmalloc(sizeof(t_list))))
		return (NULL);
	liste->prev = NULL;
	liste->next = NULL;
	liste->index = 0;
	liste->content = content;
	return (liste);
}
