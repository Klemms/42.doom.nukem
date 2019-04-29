/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 02:27:58 by cababou           #+#    #+#             */
/*   Updated: 2018/09/11 22:21:58 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsplitone(char *str, char c, int kp)
{
	t_lstcontainer	*lst;
	char			*k;

	if ((lst = ft_strsplit_lst(str, c, c, '\0')) == NULL)
		return (NULL);
	k = NULL;
	if (lstcontainer_fastsize(lst) >= 2)
	{
		if ((k = ft_strdup(ft_lstget(kp, lst->firstelement)->content)) == NULL)
		{
			ft_lstdel(lst->firstelement, 1);
			free(lst);
			return (NULL);
		}
	}
	ft_lstdel(lst->firstelement, 1);
	free(lst);
	return (k);
}
