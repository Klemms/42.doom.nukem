/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubuntil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:04:25 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 02:11:54 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubuntil(char *str, size_t start, size_t end, int free_str)
{
	char	*s;
	size_t	i;

	if (!(s = ft_strnew(end - start, 0)))
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		s[i] = str[start + i];
		i++;
	}
	if (free_str)
	{
		free(str);
		str = NULL;
	}
	return (s);
}
