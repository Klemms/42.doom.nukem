/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:38:48 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/23 16:16:34 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char *s1, char *s2, int s_free)
{
	if (s_free == 1 || s_free == 3)
		free(s1);
	if (s_free == 2 || s_free == 3)
		free(s2);
}

char		*ft_strjoin(char *s1, char *s2, int s_free)
{
	int		i;
	int		len1;
	int		len2;
	char	*dst;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(dst = (char*)malloc(sizeof(*dst) * (len1 + len2 + 1))))
		return (NULL);
	i = len1;
	while (i--)
		dst[i] = s1[i];
	i = 0;
	while (i < len2)
	{
		dst[i + len1] = s2[i];
		i++;
	}
	dst[i + len1] = '\0';
	ft_free(s1, s2, s_free);
	return (dst);
}
