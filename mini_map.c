/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:31:26 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/28 12:18:13 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void draw_a_char(int *coords, t_sdl *sdl, unsigned int *map)
{
	int rad;
	int x;
	int y;
	int center[2];

	rad = 30;
	y = coords[0];
	x = coords[1];
	center[0] = coords[0] - 15;
	center[1] = coords[1] - 15;
	coords[0] -= 30;
	coords[1] -= 30;
	while (coords[0] < y)
	{
		coords[1] = x - 30;
		while (coords[1] < x)
		{
			printf("%d %d\n",coords[0] - center[0], coords[1] - center[1]);
			if (sqrt(pow(coords[0] - center[0], 2) + (pow(coords[1] - center[1], 2))) <= 15) 
				map[sdl->map->offset * 30 * coords[0] + coords[1]] = 0xFFF;
			coords[1]++;
		}
		coords[0]++;
	}
}

void draw_a_block(int *coords, t_sdl *sdl, unsigned int *map, char type)
{
	int y;
	int x;

	if (type == 'w')
	{
		coords[0] *= 30;
	y = coords[0] + 30;
	x = coords[1] * 30 + 30;
	while (coords[0] < y)
	{
		coords[1] = x - 30;
		while (coords[1] < x)
		{
			map[sdl->map->offset * 30 * coords[0] + coords[1]] = 0xFFFFFF;
			coords[1]++;
		}
		coords[0]++;
	}
	}
	else
		draw_a_char((int[]){sdl->cam.y * MAP_H(sdl->map) * 30 / WIN_H, sdl->cam.x * MAP_W(sdl->map) * 30 / WIN_W}, sdl, map);
	
}

void draw_map(t_sdl *sdl, unsigned int *map)
{
	t_point *m = (t_point *)sdl->map->cont;

	int i = 0;

	while (i < MAP_H(sdl->map) * sdl->map->offset * 900)
		((unsigned int *)map)[++i] = 0xF;
	i = 0;
	while (i < sdl->map->offset * MAP_H(sdl->map))
	{
		if (m[i].h)
		{
			draw_a_block((int[2]){i / sdl->map->offset, i % sdl->map->offset}, sdl, map, 'w');
			 printf("%ld\n", i / sdl->map->offset);
		}
		// if (((unsigned int *)map)[(int)i] == 0x00FF00 || ((unsigned int *)map)[(int)i] == 0xFFFF00)
		// 	map[i] = 0;
		i++;
	}
	
	// float angle = sdl->cam.angle;
	// while (angle < 0.0)
	// 	angle += 2 * M_PI;
	// while (angle > 2 * M_PI)
	// 	angle -= 2 * M_PI;
	// printf("%f\n", angle);
	// ((unsigned int *)map)[sdl->cam.y / BLOCK * sdl->map->len / sdl->map->offset / 12 + sdl->cam.x / BLOCK ] = 0xFFFF00;
	 draw_a_block((int[2]){sdl->cam.x, sdl->cam.y}, sdl, map, 'p');
	// if (angle  < 1.57)
	// 	((unsigned int *)map)[(sdl->cam.y / BLOCK) * MAP_H(sdl->map) + sdl->cam.x / BLOCK] = 0x00FF00;
	// else if (angle  < 3.14)
	// 	((unsigned int *)map)[(sdl->cam.y / BLOCK ) * MAP_H(sdl->map) + sdl->cam.x / BLOCK ] = 0x00FF00;
	// else if (angle < 4.71)
	// 	((unsigned int *)map)[(sdl->cam.y / BLOCK) * MAP_H(sdl->map) + sdl->cam.x / BLOCK] = 0x00FF00;
	// else
	// 	((unsigned int *)map)[(sdl->cam.y / BLOCK ) * MAP_H(sdl->map) + sdl->cam.x / BLOCK ] = 0x00FF00;
}
