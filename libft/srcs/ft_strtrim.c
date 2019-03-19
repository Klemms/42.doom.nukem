/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:52:43 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/20 17:15:47 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	x;
	size_t			y;
	char			*dst;

	if (!s)
		return (NULL);
	x = 0;
	y = ft_strlen(s);
	if (y == 0)
		return ((char*)s);
	while (s[x] == ' ' || s[x] == '\n' || s[x] == '\t')
		x++;
	while (s[y - 1] == ' ' || s[y - 1] == '\n' || s[y - 1] == '\t')
		y--;
	if (y < x)
		return (ft_strnew(1));
	else
	{
		y = y - x;
		dst = ft_strsub(s, x, y, 0);
		return (dst);
	}
}
