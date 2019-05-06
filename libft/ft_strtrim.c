/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:19:18 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 11:36:00 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s)
{
	size_t	startws;
	size_t	endws;

	if (s == NULL)
		return (NULL);
	startws = 0;
	endws = 0;
	while (s[startws] == ' ' || s[startws] == '\n' || s[startws] == '\t')
		startws++;
	if (ft_strlen(s) == startws)
		return (ft_strsub(s, 0, 0, 0));
	while (s[ft_strlen(s) - 1 - endws] == ' ' || s[ft_strlen(s) - 1 - endws]
		== '\n' || s[ft_strlen(s) - 1 - endws] == '\t')
		endws++;
	return (ft_strsub(s, startws, ft_strlen(s) - startws - endws, 0));
}
