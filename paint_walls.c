/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:57:27 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/25 22:42:07 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

# define N 0x42F4AD
# define E 0x8A6DA3
# define W 0xBD76F7
# define S 0xF44262
# define SKY 0xA3F8FF
# define FLOUR 0x9E9380

int		paint_walls(int j, int h, float ang, char fl)
{
	if (j >= WIN_H / 2 + h)
		return (FLOUR);
	if (j < WIN_H / 2 - h || (fl == 's' && j < WIN_H / 2 + h))
		return (SKY);
	if ((fl == 'x' && QT_12(ang)))
		return (N);
	if ((fl == 'x' && QT_34(ang)))
		return (S);
	if ((fl == 'y' && QT_23(ang)))
		return (W);
	if ((fl == 'y' && QT_14(ang)))
		return (E);
	return (0xFFFFFF);
}
