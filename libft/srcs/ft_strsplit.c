/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:02:21 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/07 18:58:34 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strsplit_cntword(char const *s, char c)
{
	int i;
	int nbr_word;

	i = 0;
	nbr_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			nbr_word++;
		}
	}
	return (nbr_word);
}

static void	ft_strsplit_cntchar(char c, char const *s, char **tab)
{
	int i;
	int cnt_char;
	int cnt_word;

	i = 0;
	cnt_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt_char = 0;
			while (s[i] != c && s[i] != '\0')
			{
				i++;
				cnt_char++;
			}
			if (!(tab[cnt_word] = (char*)malloc(sizeof(tab) * (cnt_char + 1))))
				return ;
			cnt_word++;
		}
	}
}

static void	ft_strsplit_putstr(char c, char const *s, char **tab)
{
	int i;
	int cnt_char;
	int cnt_word;

	i = 0;
	cnt_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt_char = 0;
			while (s[i] != c && s[i] != '\0')
			{
				tab[cnt_word][cnt_char] = s[i];
				i++;
				cnt_char++;
			}
			tab[cnt_word][cnt_char] = '\0';
			cnt_word++;
		}
	}
	tab[cnt_word] = NULL;
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	if (!(tab = malloc(sizeof(*tab) * (ft_strsplit_cntword(s, c) + 1))))
		return (NULL);
	ft_strsplit_cntchar(c, s, tab);
	ft_strsplit_putstr(c, s, tab);
	return (tab);
}
