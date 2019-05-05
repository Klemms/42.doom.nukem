/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:40:44 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 12:22:51 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 4096

# include "libft.h"
# include <unistd.h>

typedef struct		s_file
{
	char			*content;
	int				file_descriptor;
	int				end;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
