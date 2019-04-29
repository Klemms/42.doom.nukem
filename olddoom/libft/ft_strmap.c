/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:35:26 by cababou           #+#    #+#             */
/*   Updated: 2017/12/13 19:43:04 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*nstring;

	if (s == NULL)
		return (NULL);
	i = 0;
	nstring = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (nstring == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		nstring[i] = f(s[i]);
		i++;
	}
	nstring[i] = '\0';
	return (nstring);
}
