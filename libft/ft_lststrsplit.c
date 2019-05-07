/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststrsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 01:57:32 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 02:15:24 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*char_to_str(char c)
{
	char	*str;

	if ((str = ft_strnew(1, 0)) == NULL)
		return (NULL);
	str[0] = c;
	return (str);
}

int				init_func0(char *str, t_lstcontainer **l, char **t, size_t *i)
{
	if (str == NULL || ((*l) = lstcontainer_new()) == NULL
		|| ((*t) = ft_strnew(0, 0)) == NULL)
		return (0);
	(*i) = 0;
	return (1);
}

t_lstcontainer	*ft_strsplit_lst(char *str, char c1, char c2, char c3)
{
	t_lstcontainer	*list;
	size_t			i;
	char			*tmp;

	if (init_func0(str, &list, &tmp, &i) == 0)
		return (NULL);
	while (1)
	{
		if (str[i] != c1 && str[i] != c2 && str[i] != c3)
		{
			if ((tmp = ft_strjoin(tmp, char_to_str(str[i]), 3)) == NULL)
				return (NULL);
		}
		else if (tmp[0])
		{
			lstcontainer_add(list, tmp);
			if ((tmp = ft_strnew(0, 0)) == NULL)
				return (NULL);
		}
		if (!str[i])
			ffree(tmp);
		if (!str[i])
			return (list);
		i++;
	}
}
