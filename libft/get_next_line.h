/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 03:21:32 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 05:23:49 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 20

# include "libft.h"
# include <unistd.h>

typedef struct		s_file
{
	char			*line;
	int				fd;
	int				state;
}					t_file;

int					n_gnl(int fd, char **line);

#endif
