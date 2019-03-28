/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:31:26 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/28 16:31:29 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void draw_lines(float *c, float angle, unsigned int *map, t_sdl *sdl)
{
	const float step[4] = {-5 * cos(angle + 210), 5 * sin(angle + 210), \
	-5 * cos(angle + 60), 5 * sin(angle + 60)};
	float v[5];
	
	v[0] = step[0];
	v[1] = step[1];
	v[2] = step[2];
	v[3] = step[3];
	v[4] = 0;
	while (v[4] < 15)
	{
		if (map[(sdl->map->offset * 30 * (int)(v[1] + c[1])) + (int)(v[0] \
		+ c[0])] == 0xFFFFFF || map[(sdl->map->offset * 30 * (int)(v[3] + \
		c[1])) + (int)(v[2] + c[0])] == 0xFFFFFF)
			break ;
		map[(sdl->map->offset * 30 * (int)(v[1] + c[1]))\
		 + (int)(v[0] + c[0])] = 0x00FFFF;
		map[(sdl->map->offset * 30 * (int)(v[3] + c[1]))\
		 + (int)(v[2] + c[0])] = 0x00FFFF;
	v[0] += step[0];
	v[1] += step[1];
	v[2] += step[2];
	v[3] += step[3];
		v[4]++;
	}
}

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
			if (sqrt(pow(coords[0] - center[0], 2) + (pow(coords[1] \
			- center[1], 2))) <= 15) 
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
	{
		draw_a_char((int[]){sdl->cam.y * 30 / 64 + 15, sdl->cam.x * 30 / 64 + 15}, sdl, map);
		draw_lines((float[]){sdl->cam.x * 30 / 64 , sdl->cam.y * 30 / 64}, \
		sdl->cam.angle, map, sdl);
	}
}

void draw_map(t_sdl *sdl, unsigned int *map)
{
	t_point *m;
	int 	i;

	i = 0;
	m = (t_point *)sdl->map->cont;
	while (i < MAP_H(sdl->map) * sdl->map->offset * 900)
		((unsigned int *)map)[++i] = 0xF;
	i = 0;
	while (i < sdl->map->offset * MAP_H(sdl->map))
	{
		if (m[i].h)
		{
			draw_a_block((int[2]){i / sdl->map->offset, \
			i % sdl->map->offset}, sdl, map, 'w');
		}
		i++;
	}
	 draw_a_block((int[2]){sdl->cam.x, sdl->cam.y}, sdl, map, 'p');
	
}
