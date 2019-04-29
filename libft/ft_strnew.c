/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:57:07 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 12:25:27 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*mem;
	size_t	i;

	mem = mmalloc(sizeof(char) * (size + 1));
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < (size + 1))
	{
		mem[i] = '\0';
		i++;
	}
	return (mem);
}
