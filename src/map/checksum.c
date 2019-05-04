/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 03:37:21 by cababou           #+#    #+#             */
/*   Updated: 2019/05/04 03:38:03 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.c"

unsigned int	checksum(void *data, size_t size, unsigned int seed)
{
      unsigned char *buf = (unsigned char *)data;
      size_t i;

      for (i = 0; i < size; ++i)
            seed += (unsigned int)(*buf++);
      return seed;
}
