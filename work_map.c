/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/23 21:23:56 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		first_shift_x(float ang, int *bound, int x, int y)
{
	int	first_x;

	if (ang >= 0 && ang <= M_PI / 2)
		first_x = x + (y - (*bound) * BLOCK) / tan(ang);
	else if (ang > 0 && ang <= M_PI)
		first_x = x - (y - (*bound) * BLOCK) / tan(M_PI - ang);
	else if (ang < 0 && ang >= - M_PI / 2)
	{
		(*bound)++;
		first_x = x + ((*bound) * BLOCK - y) / tan(-ang);
	}
	else
	{
		(*bound)++;
		first_x = x - ((*bound) * BLOCK - y) / tan(M_PI + ang);
	}
	return (first_x);
}

static int		first_shift_y(float ang, int *bound, int x, int y)
{
	int	first_y;

	if (ang >= 0 && ang <= M_PI / 2)
	{
		(*bound)++;
		first_y = y - ((*bound) * BLOCK - x) * tan(ang);
	}
	else if (ang > 0 && ang <= M_PI)
		first_y = y - (x - (*bound) * BLOCK) * tan(M_PI - ang);
	else if (ang < 0 && ang >= - M_PI / 2)
	{
		(*bound)++;
		first_y = y + ((*bound) * BLOCK - x) * tan(-ang);
	}
	else
		first_y = y + ((*bound) * BLOCK - x) * tan(M_PI + ang);
	return (first_y);
}

static float	get_dist_x(t_sdl *sbox, float ang)
{
	int	x;
	int	cur_r;
	int	cur_c;
	int xa;
	float dist;
	
	dist = 0.0;
	cur_r = (ang > 0) ? sbox->cam.y / BLOCK - 1 : sbox->cam.y / BLOCK;
	xa = (ang > -M_PI / 2 && ang < M_PI / 2) ?
		ABS(BLOCK / tan(ang)) : ABS(BLOCK / tan(M_PI - ang));
	x = first_shift_x(ang, &cur_r, sbox->cam.x, sbox->cam.y);
	cur_c = (ang > -M_PI / 2 && ang < M_PI / 2) ? x / BLOCK : x / BLOCK - 1;
//	printf("|angle: %.2f x_st: %d xa: %d row: %d col: %d|",
//			ang, x, xa, cur_r, cur_c);
	while (cur_c >= 0 && cur_r >= 0 && cur_c < MAP_W(sbox->map)
			&& cur_r < MAP_H(sbox->map))
	{
		if (((t_point *)sbox->map->cont)[sbox->map->offset * cur_r + cur_c].h)
		{
			printf("x[%d, %d] ", cur_c, cur_r);
			dist = sqrt(pow(sbox->cam.y - (cur_r + 1) * BLOCK, 2)
					+ pow(sbox->cam.x - x, 2));
			return (dist);
		}
		cur_r = (ang > 0) ? cur_r - 1 : cur_r + 1;
		x = (ang > -M_PI / 2 && ang < M_PI / 2) ? x + xa : x - xa;
		cur_c = (ang > -M_PI / 2 && ang < M_PI / 2) ? x / BLOCK : x / BLOCK - 1;
	}
	return (0.0);
}

static float	get_dist_y(t_sdl *sbox, float ang)
{
	int	y;
	int	cur_r;
	int	cur_c;
	int ya;
	float dist;
	
	dist = 0.0;
	cur_c = (ang > -M_PI / 2 && ang < M_PI / 2) ?
		sbox->cam.x / BLOCK : sbox->cam.x / BLOCK - 1;
	ya = (ang > -M_PI / 2 && ang < M_PI / 2) ?
		ABS(BLOCK * tan(ang)) : ABS(BLOCK * tan(M_PI - ang));
	y = first_shift_y(ang, &cur_c, sbox->cam.x, sbox->cam.y);
	cur_r = (ang > 0) ? y / BLOCK - 1 : y / BLOCK;
//	printf("|angle: %.2f y_st: %d ya: %d row: %d col: %d|",
//			ang, y, ya, cur_r, cur_c);
	while (cur_c >= 0 && cur_r >= 0 && cur_c < MAP_W(sbox->map)
			&& cur_r < MAP_H(sbox->map))
	{
		if (((t_point *)sbox->map->cont)[sbox->map->offset * cur_r + cur_c].h)
		{
		printf("y[%d, %d] ", cur_c, cur_r);
			dist = sqrt(pow(sbox->cam.x - cur_c * BLOCK, 2)
					 + pow(sbox->cam.y - y, 2));
			return (dist);
		}
		cur_c = (ang < M_PI / 2 && ang > -M_PI / 2) ? cur_c + 1 : cur_c - 1;
		y = (ang > 0) ? y - ya : y + ya;
		cur_r = (ang > 0) ? y / BLOCK - 1 : y / BLOCK;
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
	else if (sbox->cam.angle < -M_PI)
		sbox->cam.angle = 2 * M_PI + sbox->cam.angle;
	printf("map %d x %d \n", MAP_W(sbox->map), MAP_H(sbox->map));
	printf("from %d to %d grad\n", (int)((sbox->cam.angle - FOV / 2) / M_PI * 180),
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
	//	printf("<%.1f VS %.1f > ", dist, ydist);
		if (ydist > 0.1 && ydist < dist)
		{
			dist = ydist;
			printf("Y! ");
		}
		else
			printf("X! ");
		if (dist < 0.1)
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
