/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/25 22:48:34 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		first_shift_x(float ang, int bound, int x, int y)
{
	if (QT_12(ang))
		bound++;
	if (QT_14(ang))
		return (x + (y - bound * BLOCK) / tan(ang));
	else
		return (x - (y - bound * BLOCK) / tan(M_PI - ang));
}

static int		first_shift_y(float ang, int bound, int x, int y)
{
//	printf("%.1f %d %d %d | ", ang, bound, x, y);
	if (QT_23(ang))
	{
		bound++;
		ang = ang - M_PI;
	}
	if (QT_12(ang))
		return (y - (bound * BLOCK - x) * tan(ang));
	else
		return (y + (x - bound * BLOCK) * tan(ang));
}

static int		cur_column(int x, float ang) //TODO fix corners
{
//	if (x % BLOCK)
		return (x / BLOCK);
//	if (QT_23(ang))
//		return (x / BLOCK - 1);
//	return (x / BLOCK + 1);
}

static int		cur_row(int y, float ang) //TODO fix corners
{
//	if (y % BLOCK)
		return (y / BLOCK);
//	if (QT_12(ang))
//		return (y / BLOCK - 1);
//	return (y / BLOCK + 1);
}

static float	get_dist_x(t_sdl *sbox, float ang, int *fl)
{
	int	x;
	int	next_r;
	int	cur_c;
	int xa;

	*fl = 1;	
	next_r = (QT_12(ang)) ? sbox->cam.y / BLOCK - 1 : sbox->cam.y / BLOCK + 1;
	xa = ABS(BLOCK / tan((QT_14(ang)) ? ang : M_PI - ang));
	x = first_shift_x(ang, next_r, sbox->cam.x, sbox->cam.y);
	cur_c = cur_column(x, ang);
//	printf("fsX %d nextR %d ", x, next_r);
	while (cur_c >= 0 && cur_c < MAP_W(sbox->map) && next_r >= 0 &&
			next_r < MAP_H(sbox->map))
	{
//			printf("x[%d %d] ", x, next_r);
		if (((t_point *)sbox->map->cont)[sbox->map->offset * next_r + cur_c].h)
		{
			return (sqrt(pow(sbox->cam.y -
					(QT_12(ang) ? next_r + 1 : next_r) * BLOCK, 2) +
						pow(sbox->cam.x - x, 2)));
		}
		next_r = (QT_12(ang)) ? next_r - 1 : next_r + 1;
		x = (QT_14(ang)) ? x + xa : x - xa;
		cur_c = cur_column(x, ang);
	}
	*fl = 0;
	return (sqrt(pow(sbox->cam.y - (QT_12(ang) ? next_r + 1 : next_r) * BLOCK, 2) + pow(sbox->cam.x - x, 2)));
}

static float	get_dist_y(t_sdl *sbox, float ang, int *fl)
{
	int	y;
	int	cur_r;
	int	next_c;
	int ya;

	*fl = 1;	
	next_c = (QT_14(ang)) ? sbox->cam.x / BLOCK + 1 : sbox->cam.x / BLOCK - 1;
	ya = ABS(BLOCK * tan((QT_14(ang)) ? ang : M_PI - ang));
	y = first_shift_y(ang, next_c, sbox->cam.x, sbox->cam.y);
	cur_r = cur_row(y, ang);
//	cur_r = y / BLOCK;
//	printf("fsY %d nextC %d ", y, next_c);
	while (next_c >= 0 && next_c < MAP_W(sbox->map) && cur_r >= 0 &&
			cur_r < MAP_H(sbox->map))
	{
//		printf("y[%d %d] ", next_c, y);
		if (((t_point *)sbox->map->cont)[sbox->map->offset * cur_r + next_c].h)
		{
//			printf("get it! --- ");
//			printf("y[%d %d] ", cur_r, next_c);
			return (sqrt(pow(sbox->cam.x -
					(QT_23(ang) ? next_c + 1 : next_c) * BLOCK, 2) +
					 pow(sbox->cam.y - y, 2)));
		}
		next_c = QT_14(ang) ? next_c + 1 : next_c - 1;
		y = QT_12(ang) ? y - ya : y + ya;
//		cur_r = y / BLOCK - (y % BLOCK) ? 0 : 1;
		cur_r = cur_row(y, ang);
	}
	*fl = 0;
	return (sqrt(pow(sbox->cam.x - (QT_23(ang) ? next_c + 1 : next_c) * BLOCK, 2) + pow(sbox->cam.y - y, 2)));
}

void	cast_walls(t_sdl *sbox, unsigned int *map)
{
	int	i;
	int	j;
	float dist;
	float ydist;
	int h;
	float ang;
	char	fl;

	printf("map %d x %d \n", MAP_W(sbox->map), MAP_H(sbox->map));
	printf("I m in [%d %d] looking at %d grad ", sbox->cam.x / BLOCK,
			sbox->cam.y / BLOCK, (int)(sbox->cam.angle / M_PI * 180));
	printf("(from %d to %d grad)\n", 
			(int)((sbox->cam.angle - FOV / 2) / M_PI * 180),
			(int)((sbox->cam.angle + FOV / 2) / M_PI * 180));
	ang = sbox->cam.angle + FOV / 2;
	i = -1;
	while (++i < WIN_W)
	{
		if (ang > M_PI)
			ang = -(2 * M_PI - ang);
		else if (ang < -M_PI)
			ang = 2 * M_PI + ang;
		int flx, fly;
		dist = get_dist_x(sbox, ang, &flx);
		ydist = get_dist_y(sbox, ang, &fly);
//		printf("<%.1f VS %.1f > ", dist, ydist);
		if (!flx && !fly)
		{
			fl = 's';
			if (ydist < dist)
				dist = ydist;
//			printf("0! ");
		}
		else
		{
			fl = 'x';
			if ((fly && ydist < dist) || !flx)
			{
				dist = ydist;
				fl = 'y';
//				printf("Y! ");
			}
//			else
//				printf("X! ");
		//	dist *= cos(ang - sbox->cam.angle);
		//	h = WALL_H * DIST / dist;
		}
			dist *= cos(ang - sbox->cam.angle);
			h = WALL_H * DIST / dist;
		j = -1;
		while (++j < WIN_H)
		{
//			if (j > WIN_H / 2 - h && j < WIN_H / 2 + h)
				map[i + j * WIN_W] = paint_walls(j, h, ang, fl);
//			else
//				map[i + j * WIN_W] = 0x0;
		}
		ang -= STEP;
	}
}
