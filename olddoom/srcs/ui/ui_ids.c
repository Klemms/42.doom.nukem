/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_ids.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 05:30:01 by cababou           #+#    #+#             */
/*   Updated: 2019/04/18 05:31:50 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_ids(t_doom *doom)
{
	doom->ui_ids = 1;
}

int		next_id(t_doom *doom)
{
	return (doom->ui_ids++);
}
