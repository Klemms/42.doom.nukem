/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:59:01 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/12 11:37:50 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct	s_xy
{
	double		x;
	double		y;
	struct s_xy	*next;
}				t_xy;

typedef struct	s_xyz
{
	double	x;
	double	y;
	double	z;
}				t_xyz;

typedef struct	s_sector
{
	double			floor;
	double			ceil;
	t_xy			*vertex;
	signed char		*neighbors;
	int				pts;
	struct s_sector	*next;
}				t_sector;

typedef struct	s_player
{
	t_xyz		where;
	t_xyz		velocity;
	double		angle;
	double		anglesin;
	double		anglecos;
	double		yaw;
	unsigned	sector;
}				t_player;

typedef struct	s_read
{
	char		*line;
	char		**split;
	t_xy		*vert;
	t_xy		*vertices;
	t_sector	*sect;
	int			v;
	int			m;
	int			num_vertices;
}				t_read;

void			ft_free_split(char **split);
void			ft_read_vertices(t_read *r);
void			ft_tab_vertices(t_read *r);

#endif