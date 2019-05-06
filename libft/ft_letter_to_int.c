/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_letter_to_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 02:58:45 by cababou           #+#    #+#             */
/*   Updated: 2018/09/04 03:00:33 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		letter_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c == 'A' || c == 'a')
		return (10);
	else if (c == 'B' || c == 'b')
		return (11);
	else if (c == 'C' || c == 'c')
		return (12);
	else if (c == 'D' || c == 'd')
		return (13);
	else if (c == 'E' || c == 'e')
		return (14);
	else if (c == 'F' || c == 'f')
		return (15);
	return (0);
}
