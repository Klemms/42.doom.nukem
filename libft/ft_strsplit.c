/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:58:14 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 11:35:01 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	spstrlen(char *s, int start, char until)
{
	size_t	i;

	i = 0;
	while (s[start + i] != until && s[start + i] != '\0')
	{
		i++;
	}
	return (i);
}

static size_t	countwords(char *s, char c)
{
	size_t	i;
	size_t	count;
	int		makeword;

	i = 0;
	count = 0;
	makeword = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			makeword = 0;
		if (s[i] != c && makeword == 0)
		{
			makeword = 1;
			count++;
		}
		i++;
	}
	return (count);
}

int				strsplit_size(char **array)
{
	size_t i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void			free_strsplit(char **array)
{
	size_t i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		ffree(array[i]);
		i++;
	}
	ffree(array);
}

char			**ft_strsplit(char *s, char c)
{
	size_t	i;
	size_t	y;
	char	**table;

	if (s == NULL)
		return (NULL);
	i = 0;
	table = mmalloc(2 * (sizeof(char **) * (countwords(s, c) + 1)));
	if (table == NULL)
		return (NULL);
	y = 0;
	while (i < countwords(s, c))
	{
		while (s[y] == c)
			y++;
		table[i] = ft_strsub(s, y, spstrlen(s, y, c), 0);
		y += spstrlen(s, y, c);
		i++;
	}
	table[i] = NULL;
	return (table);
}
