/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 19:55:14 by cababou           #+#    #+#             */
/*   Updated: 2018/08/12 03:36:06 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstadd(t_list *listelement, t_list *newelement)
{
	newelement->index = (listelement->index + 1);
	newelement->prev = listelement;
	newelement->next = NULL;
	listelement->next = newelement;
	return (newelement);
}
