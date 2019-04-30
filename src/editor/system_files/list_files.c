/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:52:43 by cababou           #+#    #+#             */
/*   Updated: 2019/04/29 21:51:56 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <dirent.h>

t_lstcontainer	*list_files(char *folder_path)
{
	t_lstcontainer	*files;
	DIR				*directory;
	struct dirent	*dir;

	if (!(files = lstcontainer_new())
		&& !(directory = opendir(folder_path)))
		return (NULL);
	while ((dir = readdir(directory)))
	{
		lstcontainer_add(files, ft_strdup(dir->d_name));
		free(dir);
		dir = NULL;
	}
	return (files);
}