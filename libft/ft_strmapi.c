/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:42:49 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 12:25:23 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*nstring;

	if (s == NULL)
		return (NULL);
	i = 0;
	nstring = mmalloc(sizeof(char) * (ft_strlen(s) + 1));
	if (nstring == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		nstring[i] = f(i, s[i]);
		i++;
	}
	nstring[i] = '\0';
	return (nstring);
}
