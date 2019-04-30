/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:24:22 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 17:17:13 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			init_texture(t_doom *doom)
{
	int		i;
	t_list	*lst;
	char	*tmp_txture;

	i = -1;
	lst = doom->textures->firstelement;
	while (lst && ++i < 4)
	{
		tmp_txture = (char *)lst->content;
		/*if (!(doom->texture[i].ptr = mlx_xpm_file_to_image(doom->mlx,
		tmp_txture, &(doom->texture[i].width), &(doom->texture[i].height))))
			return (0);
		if (!(doom->texture[i].img.ptr = mlx_xpm_file_to_image(doom->mlx, tmp_txture,
													&(doom->texture[i].width),
													&(doom->texture[i].height))))
			return (0);
		doom->texture[i].img.img = mlx_get_data_addr(doom->texture[i].img.ptr,
												&(doom->texture[i].img.bpp),
												&(doom->texture[i].img.s_l),
												&(doom->texture[i].img.endian));*/
		lst = lst->next;
	}
	return (1);
}