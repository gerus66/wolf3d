/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/23 00:03:10 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static float	get_dist_x(t_sdl *sbox, float ang)
{
	t_point *cp;
	int	x;
	int	cur_r;
	int	cur_c;
	int xa;
	float dist = 0.0;

	cur_r = sbox->cam.y / BLOCK;
	xa = ABS(BLOCK / tan(ang));
	x = sbox->cam.x + (sbox->cam.y - cur_r * BLOCK) / tan(ang);
	cur_c = x / BLOCK;
	cp = (t_point *)sbox->map->cont;
//	printf("|angle: %.2f x_st: %d xa: %d row: %d col: %d|",
//			ang, x, xa, cur_r, cur_c);
	while (cur_c >= 0 && cur_r >= 0 && cur_c < WIN_W && cur_r < WIN_H)
	{
		if (cp[sbox->map->offset * cur_r + cur_c].h)
		{
			printf("x[%d, %d] ", cur_c, cur_r);
			dist = sqrt(pow((sbox->cam.y / BLOCK - cur_r) * BLOCK + 
					(int)(0.5 * BLOCK), 2) + pow(x - sbox->cam.x, 2));
			return (dist);
		}
		cur_r = (ang > 0) ? cur_r - 1 : cur_r + 1;
		x = (ang > -M_PI / 2 && ang < M_PI / 2) ? x + xa : x - xa;
		cur_c = x / BLOCK;
	}
	return (0.0);
}

static float	get_dist_y(t_sdl *sbox, float ang)
{
	t_point *cp;
	int	y;
	int	cur_r;
	int	cur_c;
	int ya;
	float dist = 0.0;

	cur_c = sbox->cam.x / BLOCK;
	ya = ABS(BLOCK * tan(ang));
	y = (ang < M_PI / 2 && ang > -M_PI / 2) ? (cur_c + 1) * BLOCK - sbox->cam.x :
		cur_c * BLOCK - sbox->cam.x;
	y = sbox->cam.y - y * tan(ang);
	cur_r = y / BLOCK;
	cp = (t_point *)sbox->map->cont;
//	printf("|angle: %.2f y_st: %d ya: %d row: %d col: %d|",
//			ang, y, ya, cur_r, cur_c);
	while (cur_c >= 0 && cur_r >= 0 && cur_c < WIN_W && cur_r < WIN_H)
	{
		if (cp[sbox->map->offset * cur_r + cur_c].h)
		{
		printf("y[%d, %d] ", cur_c, cur_r);
			dist = sqrt(pow((sbox->cam.x / BLOCK - cur_c) * BLOCK + 
					(int)(0.5 * BLOCK), 2) + pow(y - sbox->cam.y, 2));
			return (dist);
		}
		cur_c = (ang < M_PI / 2 && ang > -M_PI / 2) ? cur_c + 1 : cur_c - 1;
		y = (ang > 0) ? y - ya : y + ya;
		cur_r = y / BLOCK;
	}
	return (0.0);
}

void	work_it(t_sdl *sbox, unsigned int *map, int len)
{
	int	i;
	int	j;
	float dist;
	float ydist;
	int h;
	float ang;

	len++;//
	if (sbox->cam.angle > M_PI)
		sbox->cam.angle = -(2 * M_PI - sbox->cam.angle);
	if (sbox->cam.angle < -M_PI)
		sbox->cam.angle = 2 * M_PI + sbox->cam.angle;
	printf("from %d to %d grad\n", (int)((sbox->cam.angle - FOV / 2) / M_PI * 180),
			(int)((sbox->cam.angle + FOV / 2) / M_PI * 180));
	ang = sbox->cam.angle + FOV / 2;
	i = -1;
	while (++i < WIN_W)
	{
		dist = get_dist_x(sbox, ang);
		ydist = get_dist_y(sbox, ang);
	//	printf("<%.1f VS %.1f > ", dist, ydist);
		if (ydist > 0.1 && ydist < dist)
		{
			dist = ydist;
			printf("Y! ");
		}
		if (dist < 0.1)
			h = 0;
		else
		{
			dist *= cos(ang - sbox->cam.angle);
			h = WALL_H * DIST / dist;
			printf("X! ");
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
