/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:56:02 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/15 17:59:26 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_base(char *base)
{
	int i;
	int j;

	i = 0;
	while (base[i] != '\0')
	{
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j] || base[i] == '-' || base[i] == '+')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (i);
}

static void	ft_from_base_ten(int nbr, int base_int, char *base)
{
	if (nbr < base_int)
		ft_putchar(base[nbr]);
	else
	{
		ft_from_base_ten(nbr / base_int, base_int, base);
		ft_from_base_ten(nbr % base_int, base_int, base);
	}
}

void		ft_putnbr_base(int nbr, char *base)
{
	int base_int;

	base_int = ft_find_base(base);
	if (base_int >= 2)
	{
		if (nbr < 0)
		{
			ft_putchar('-');
			nbr = -nbr;
			ft_from_base_ten(nbr, base_int, base);
		}
		else
			ft_from_base_ten(nbr, base_int, base);
	}
}
