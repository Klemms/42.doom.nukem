/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:38:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/18 02:58:40 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define MAX_WAIT 32
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
