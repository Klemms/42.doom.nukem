/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:50:48 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/08 12:47:45 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*dupli;

	size = ft_strlen(s);
	dupli = (char *)malloc(sizeof(*dupli) * (size + 1));
	if (dupli == NULL)
		return (NULL);
	size = 0;
	while (s[size] != '\0')
	{
		dupli[size] = s[size];
		size++;
	}
	dupli[size] = '\0';
	return (dupli);
}
