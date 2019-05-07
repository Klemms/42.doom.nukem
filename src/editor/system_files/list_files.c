/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:52:43 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 15:55:32 by lde-batz         ###   ########.fr       */
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
		|| !(directory = opendir(folder_path)))
		return (NULL);
	while ((dir = readdir(directory)))
	{
		if (dir->d_type == DT_REG)
			lstcontainer_add(files, ft_strdup(dir->d_name));
	}
	closedir(directory);
	return (files);
}
