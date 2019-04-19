/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:38:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/22 18:32:42 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define MAX_WAIT 32
# define ANGLE_H 0.73f * WIN_H
# define ANGLE_V 0.2f * WIN_H

typedef struct	s_i_xy
{
	int	x;
	int	y;
}				t_i_xy;

typedef struct	s_window
{
	int	sector;
	int	x1;
	int	x2;
}				t_window;

double			ft_clamp(double a, double min, double max);
t_xy			ft_intersect_lines(t_xy p1, t_xy p2, t_xy p3, t_xy p4);

#endif
