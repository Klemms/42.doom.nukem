/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 05:26:33 by cababou           #+#    #+#             */
/*   Updated: 2019/05/04 12:31:19 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memjoin(void *m1, void *m2, size_t s1, size_t s2)
{
	void	*final;
	size_t	sz;
	size_t	i;

	sz = s1 + s2;
	if (!(final = mmalloc(sz)))
		return (NULL);
	i = 0;
	while (i < s1)
	{
		((char *)final)[i] = ((char *)m1)[i];
		i++;
	}
	while (i < sz)
	{
		((char *)final)[i] = ((char *)m2)[i - s1];
		i++;
	}
	return (final);
}
