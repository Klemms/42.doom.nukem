/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:38:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/12 12:10:11 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define MAX_WAIT 32
# define ANGLE_H 0.73f * WIN_H
# define ANGLE_V 0.2f * WIN_H
# define CLEIS 0xaaaaaa
# define WALL 0x505050
# define RED 0xff0000
# define GREEN 0x00ff00
# define BLUE 0x0000ff

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

#endif
