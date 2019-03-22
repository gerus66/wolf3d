/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/22 17:56:09 by mbartole         ###   ########.fr       */
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
	int	cur_r = x / BLOCK - 1;
	int	cur_c = y / BLOCK - 1;

	float xa = BLOCK / tan(ang);
	float ya = BLOCK * tan(ang);
	int dist = 0;
//	int i = cam_r;
//	printf("cur_c %d cur_r %d xa %.2f ya %.2f\n", cur_c, cur_r, xa, ya);
	printf("X: ");
	while (cur_c >= 0 && cur_r >= 0 && cur_c < len)
	{
	//	printf("X col %d, row %d xa %.5f ---> \n", cur_c, cur_r, xa);
	//	printf("gor %d\n", x);
		x += xa;
		cur_c = x / BLOCK;
	//	printf("X col %d, row %d \n", cur_c, cur_r);
		if (cp[sbox->map->offset * cur_r + cur_c].h)
		{
		printf(" [%d, %d, %.2f] ", cur_c, cur_r, ang);
			dist = sqrt(pow((sbox->cam.y / BLOCK - cur_r) * BLOCK + 
					(int)(0.5 * BLOCK), 2) + pow(x - sbox->cam.x, 2));
			break ;
		}
		cur_r--;
	}
//	printf("\n");
	if (dist)
		return (dist);
	x = sbox->cam.x;
	y = sbox->cam.y;
	cur_r = x / BLOCK;
	cur_c = y / BLOCK;
	int x2, y2;
	printf("X: ");
	while (cur_c >= 0  && cur_r >= 0 && cur_c < len)
	{
	//	printf("Y col %d, row %d xa %.5f ---> \n", cur_c, cur_r, xa);
		y -= ya;
		cur_c = y / BLOCK;
	//	printf("Y col %d, row %d \n", cur_c, cur_r);
		if (cp[sbox->map->offset * cur_r + cur_c].h)
		{
		printf(" [%d, %d, %1.f] ", cur_c, cur_r, ang);
			x2 = (sbox->cam.x / BLOCK - cur_c + 0.5);
	//		printf("x^2 %d\n", x2);
			x2 = pow(x2, 2);
	//		printf("x^2 %d\n", x2);
			y2 = pow(y - sbox->cam.y, 2);
	//		printf("y^2 %d\n", y2);
			dist = sqrt(x2 + y2);
			break ;
		}
		cur_c--;
	}
//	printf("\n");
	return (dist);	
}

void	work_it(t_sdl *sbox, unsigned int *map, int len)
{
	int	i = -1;
	int	j = -1;
	int dist;
	int h;
	float ang = sbox->cam.angle - FOV / 2;

	dist = get_dist(sbox, sbox->cam.angle, len);
	printf("correction angle: %.2f\n", ang - sbox->cam.angle);
	dist *= cos(ang - sbox->cam.angle);
	printf("dist %d, main height %d\n", dist, (WALL_H * DIST / dist));
	while (++i < WIN_W)
	{
		dist = get_dist(sbox, ang, len);
	printf("correction angle: %.2f\n", ang - sbox->cam.angle);
	dist *= cos(ang - sbox->cam.angle);
		if (dist)
			h = WALL_H * DIST / dist;
		else
			h = 0;
//		printf("[%d %f %d] \n", i, ang, h);
		j = -1;
		while (++j < WIN_H)
		{
			if (j < h)
				map[i + j * len] = 0x42F4AD;
		}
		ang += STEP;
	}
}
