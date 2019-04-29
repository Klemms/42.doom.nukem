/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:24:22 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 14:16:41 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

int			check_extension(char *ext, char *file_name)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (file_name[++i])
		;
	while (ext[++j])
		;
	while (--j >= 0 && --i >= 0)
	{
		if (ext[j] != file_name[i])
			break ;
	}
	if (j != -1)
		return (0);
	return (1);
}

int			init_texture(t_wolf *w)
{
	int		i;
	t_list	*lst;
	char	*tmp_txture;

	i = -1;
	lst = w->textures->firstelement;
	while (lst && ++i < 4)
	{
		tmp_txture = (char *)lst->content;
		if (!check_extension(".xpm", tmp_txture))
			return (0);
		if (!(w->texture[i].img.ptr = mlx_xpm_file_to_image(w->mlx, tmp_txture,
													&(w->texture[i].width),
													&(w->texture[i].height))))
			return (0);
		w->texture[i].img.img = mlx_get_data_addr(w->texture[i].img.ptr,
												&(w->texture[i].img.bpp),
												&(w->texture[i].img.s_l),
												&(w->texture[i].img.endian));
		lst = lst->next;
	}
	return (1);
}
