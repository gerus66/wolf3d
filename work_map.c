/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/25 00:11:55 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		first_shift_x(float ang, int bound, int x, int y)
{
	if (ang > 0)
		bound++;
	if (ang + M_PI / 2 >= 0)
		return (x + (y - bound * BLOCK) / tan(ang));
	else
		return (x - (y - bound * BLOCK) / tan(M_PI - ang));
}

static int		first_shift_y(float ang, int bound, int x, int y)
{
//	printf("%.1f %d %d %d | ", ang, bound, x, y);
	if (ang > M_PI / 2 || ang < -M_PI / 2)
		bound++;
	if (ang > M_PI / 2 || ang < -M_PI / 2)
		ang = ang - M_PI;
	if (ang >= 0)
		return (y - (bound * BLOCK - x) * tan(ang));
	else
		return (y + (x - bound * BLOCK) * tan(ang));
}

static float	get_dist_x(t_sdl *sbox, float ang)
{
	int	x;
	int	next_r;
	int	cur_c;
	int xa;
	
	next_r = (ang >= 0) ? sbox->cam.y / BLOCK - 1 : sbox->cam.y / BLOCK + 1;
	xa = ABS(BLOCK / tan((ang <= M_PI / 2 && ang >= -M_PI / 2) ? ang : M_PI - ang));
	x = first_shift_x(ang, next_r, sbox->cam.x, sbox->cam.y);
	cur_c = x / BLOCK;
	while (cur_c >= 0 && cur_c < MAP_W(sbox->map) && next_r >= 0 &&
			next_r < MAP_H(sbox->map))
	{
		if (((t_point *)sbox->map->cont)[sbox->map->offset * next_r + cur_c].h)
		{
			printf("x[%d %d] ", next_r, cur_c);
			return (sqrt(pow(sbox->cam.y -
					(ang > 0 ? next_r + 1 : next_r) * BLOCK, 2) +
						pow(sbox->cam.x - x, 2)));
		}
		next_r = (ang > 0) ? next_r - 1 : next_r + 1;
		x = (ang <= M_PI / 2 && ang >= -M_PI / 2) ? x + xa : x - xa;
		cur_c = x / BLOCK;
	}
	return (0.0);
}

static float	get_dist_y(t_sdl *sbox, float ang)
{
	int	y;
	int	cur_r;
	int	next_c;
	int ya;
	
	next_c = (ang <= M_PI / 2 && ang >= -M_PI / 2) ?
		sbox->cam.x / BLOCK + 1 : sbox->cam.x / BLOCK - 1;
	ya = ABS(BLOCK * tan((ang <= M_PI / 2 && ang >= -M_PI / 2) ? ang : M_PI - ang));
	y = first_shift_y(ang, next_c, sbox->cam.x, sbox->cam.y);
	cur_r = y / BLOCK;
//	printf("fsh %d curr %d ", y, cur_r);
	while (next_c >= 0 && next_c < MAP_W(sbox->map) && cur_r >= 0 &&
			cur_r < MAP_H(sbox->map))
	{
//		printf("y[%d %d] ", cur_r, next_c);
		if (((t_point *)sbox->map->cont)[sbox->map->offset * cur_r + next_c].h)
		{
//			printf("get it! --- ");
			printf("y[%d %d] ", cur_r, next_c);
			return (sqrt(pow(sbox->cam.x -
					(ang > M_PI / 2 || ang < -M_PI / 2 ? next_c + 1 : next_c) * BLOCK, 2) +
					 pow(sbox->cam.y - y, 2)));
		}
		next_c = (ang <= M_PI / 2 && ang >= -M_PI / 2) ? next_c + 1 : next_c - 1;
		y = (ang > 0) ? y - ya : y + ya;
		cur_r = y / BLOCK;
	}
	return (0.0);
}

void	work_it(t_sdl *sbox, unsigned int *map)
{
	int	i;
	int	j;
	float dist;
	float ydist;
	int h;
	float ang;

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
		dist = get_dist_x(sbox, ang);
		ydist = get_dist_y(sbox, ang);
		printf("<%.1f VS %.1f > ", dist, ydist);
		if (ydist > 0.1 && ydist < dist)
		{
			dist = ydist;
			printf("Y! ");
		}
		else
//			;
			printf("X! ");
		if (dist < 0.001)
		{
			h = 0;
			printf("0! ");
		}
		else
		{
			dist *= cos(ang - sbox->cam.angle);
			h = WALL_H * DIST / dist;
		}
		j = -1;
		while (++j < WIN_H)
		{
			if (j > WIN_H / 2 - h && j < WIN_H / 2 + h)
				map[i + j * WIN_W] = 0x42F4AD;
			else
				map[i + j * WIN_W] = 0x0;
		}
		ang -= STEP;
	}
}
