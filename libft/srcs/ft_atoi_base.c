/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 09:31:34 by lde-batz          #+#    #+#             */
/*   Updated: 2018/12/13 15:26:48 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_test_atoi(char *str, char *base, int base_int)
{
	int i;
	int j;
	int compt;

	if (str[0] == '\0' || base_int < 2)
		return (0);
	i = 0;
	if (str[i] == 43 || str[i] == 45)
		i++;
	while (str[i] != '\0')
	{
		compt = 0;
		j = 0;
		while (base[j] != '\0')
		{
			if (base[j] == ft_tolower(str[i]))
				compt++;
			j++;
		}
		if (compt != 1)
			return (0);
		i++;
	}
	return (1);
}

int		ft_find_base(char *base)
{
	int i;
	int j;

	i = 0;
	while (base[i] != '\0')
	{
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j] || base[i] == '+' || base[i] == '-'
					|| base[j] == '+' || base[j] == '-')
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

int		ft_conversion(char *str, char *base, int base_int, int size_of)
{
	int res;
	int i;
	int j;
	int neg;

	res = 0;
	i = 0;
	neg = 0;
	while (i <= size_of)
	{
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[0] == '-')
				neg++;
			i++;
		}
		j = 0;
		while (ft_tolower(str[i]) != base[j])
			j++;
		res = res * base_int + j;
		i++;
	}
	if (neg)
		return (-res);
	return (res);
}

int		ft_atoi_base(char *str, char *base)
{
	int *res;
	int base_int;
	int size_of;

	if (!str || !base)
		return (0);
	res = (int*)malloc(sizeof(*res) * 11);
	base_int = ft_find_base(base);
	if (ft_test_atoi(str, base, base_int))
	{
		size_of = 0;
		while (str[size_of] != '\0')
			size_of++;
		size_of--;
		return (ft_conversion(str, base, base_int, size_of));
	}
	else
		return (0);
}
