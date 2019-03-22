/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/22 18:58:13 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
/*
void	work_map(t_sdl *sbox, unsigned int *map, int len)
{
	int		i;
	int		map_size;
	t_point	*cp;

	i = -1;
	map_size = sbox->map->len / sizeof(t_point);
	cp = (t_point *)sbox->map->cont;
	printf("%f, %f\n", STEP, DIST);
	while (++i < map_size)
	{
		map[i] = 0x00FF;
//		if (cp[i].h)
//	    	map[100500 + i % sbox->map->offset + i / sbox->map->offset * len] = 0x42F4AD;
//		else
//			map[100500 + i % sbox->map->offset + i / sbox->map->offset * len] = 0xFFFFFF;
	}
}*/

int	get_dist(t_sdl *sbox, float ang, int len)
{
	t_point *cp;
	cp = (t_point *)sbox->map->cont;

	int	x = sbox->cam.x;
	int	y = sbox->cam.y;
	int	cur_r = y / BLOCK - 1;
	int	cur_c = x / BLOCK - 1;

	float xa = BLOCK / tan(ang);
	float ya = BLOCK * tan(ang);
	int dist = 0;
	printf("X: %.1f %d\n", xa, signbit(xa));
	while (cur_c >= 0 && cur_r >= 0 && cur_c < len)
	{
		x -= xa;
		cur_c = x / BLOCK - 1;
		if (cp[sbox->map->offset * cur_r + cur_c].h)
		{
			dist = sqrt(pow((sbox->cam.y / BLOCK - cur_r) * BLOCK + 
					(int)(0.5 * BLOCK), 2) + pow(x - sbox->cam.x, 2));
			break ;
		}
		cur_r--;
	}
	if (dist)
		return (dist);
	x = sbox->cam.x;
	y = sbox->cam.y;
	cur_r = y / BLOCK - 1;
	cur_c = x / BLOCK - 1;
	printf("Y: \n");
	while (cur_c >= 0  && cur_r >= 0 && cur_c < len)
	{
		y -= ya;
		cur_r = y / BLOCK - 1;
		if (cp[sbox->map->offset * cur_r + cur_c].h)
		{
			dist = sqrt(pow((sbox->cam.x / BLOCK - cur_c) * BLOCK + 
					(int)(0.5 * BLOCK), 2) + pow(y - sbox->cam.y, 2));
			break ;
		}
		cur_c++;
	}
	return (dist);	
}

void	work_it(t_sdl *sbox, unsigned int *map, int len)
{
	int	i = -1;
	int	j = -1;
	float dist;
	int h;
	float ang = sbox->cam.angle - FOV / 2;

	dist = get_dist(sbox, sbox->cam.angle, len);
	printf("angle: %.0f\n", sbox->cam.angle / M_PI * 180);
	dist *= cos(ang - sbox->cam.angle);
	printf("dist %f, main height %f\n", dist, (WALL_H * DIST / dist));
	while (++i < WIN_W)
	{
		dist = get_dist(sbox, ang, len);
	dist *= cos(ang - sbox->cam.angle);
		if (dist > 0.001)
			h = WALL_H * DIST / dist;
		else
			h = 0;
		j = -1;
		while (++j < WIN_H)
		{
			if (j < h)
				map[i + j * len] = 0x42F4AD;
			else
				map[i + j * len] = 0x0;
		}
		ang += STEP;
	}
}
