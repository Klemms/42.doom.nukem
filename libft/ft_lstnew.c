/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 20:10:57 by cababou           #+#    #+#             */
/*   Updated: 2018/08/11 04:37:32 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content)
{
	t_list		*liste;

	if ((liste = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	liste->prev = NULL;
	liste->next = NULL;
	liste->index = 0;
	if (content == NULL)
	{
		liste->content = NULL;
		return (liste);
	}
	liste->content = (void *)content;
	return (liste);
}
