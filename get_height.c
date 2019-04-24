/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/24 15:03:21 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static float	first_shift_x(float ang, int bound, int x, int y)
{
	if (QT_12(ang))
		bound++;
	if (QT_14(ang))
		return ((float)x + ((float)y - bound * BLOCK) / tan(ang));
	else
		return ((float)x - ((float)y - bound * BLOCK) / tan(M_PI - ang));
}

static float	first_shift_y(float ang, int bound, int x, int y)
{
	if (QT_23(ang))
	{
		bound++;
		ang = ang - M_PI;
	}
	if (QT_12(ang))
		return ((float)y - (bound * BLOCK - (float)x) * tan(ang));
	else
		return ((float)y + ((float)x - bound * BLOCK) * tan(ang));
}

static float	get_dist_x(t_sdl *sbox, float ang, char *fl, int *offset)
{
	int		next_r;
	int		cur_c;
	float	xa;
	float	x;

	next_r = (QT_12(ang)) ? sbox->cam.y / BLOCK - 1 : sbox->cam.y / BLOCK + 1;
	xa = fabs(BLOCK / tan((QT_14(ang)) ? ang : M_PI - ang));
	x = first_shift_x(ang, next_r, sbox->cam.x, sbox->cam.y);
	cur_c = (int)x / BLOCK;
	while (1)
	{
		if ((cur_c >= MAP_W(sbox->map) || x < 0 ||
			next_r >= MAP_H(sbox->map) || next_r <= -1) ||
			(MAP(sbox->map)[sbox->map->offset * next_r + cur_c].h && (*fl = 1)))
		{
			*offset = (int)x;
			return (sqrt(pow(sbox->cam.y -
				(QT_12(ang) ? next_r + 1 : next_r) * BLOCK, 2) +
				pow(sbox->cam.x - x, 2)));
		}
		next_r = (QT_12(ang)) ? next_r - 1 : next_r + 1;
		x = (QT_14(ang)) ? x + xa : x - xa;
		cur_c = (int)x / BLOCK;
	}
	return (0.0);
}

static float	get_dist_y(t_sdl *sbox, float ang, char *fl, int *offset)
{
	int		cur_r;
	int		next_c;
	float	ya;
	float	y;

	next_c = (QT_14(ang)) ? sbox->cam.x / BLOCK + 1 : sbox->cam.x / BLOCK - 1;
	ya = fabs(BLOCK * tan((QT_14(ang)) ? ang : M_PI - ang));
	y = first_shift_y(ang, next_c, sbox->cam.x, sbox->cam.y);
	cur_r = (int)y / BLOCK;
	while (1)
	{
		if ((cur_r >= MAP_H(sbox->map) || y < 0 ||
			next_c >= MAP_W(sbox->map) || next_c <= -1) ||
			(MAP(sbox->map)[sbox->map->offset * cur_r + next_c].h && (*fl = 1)))
		{
			*offset = (int)y;
			return (sqrt(pow(sbox->cam.x -
					(QT_23(ang) ? next_c + 1 : next_c) * BLOCK, 2) +
					pow(sbox->cam.y - y, 2)));
		}
		next_c = QT_14(ang) ? next_c + 1 : next_c - 1;
		y = QT_12(ang) ? y - ya : y + ya;
		cur_r = (int)y / BLOCK;
	}
	return (0.0);
}

float			get_height(t_sdl *sbox, float ang, int *offset, char *fl)
{
	char	ya_fl;
	int		ya_offset;
	float	dist;
	float	disty;

	dist = get_dist_x(sbox, ang, fl, offset);
	ya_fl = 0;
	ya_offset = 0;
	disty = get_dist_y(sbox, ang, &ya_fl, &ya_offset);
	if (!(*fl) && !ya_fl && (*fl = 's'))
		return (WALL_H * DIST / (disty < dist ? disty : dist)
				/ cos(ang - sbox->cam.angle));
	else
	{
		if ((ya_fl && disty < dist) || !(*fl))
		{
			*offset = ya_offset;
			*fl = 'y';
			dist = disty;
		}
		else
			*fl = 'x';
		return (WALL_H * DIST / dist / cos(ang - sbox->cam.angle));
	}
}
