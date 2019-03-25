/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:31:26 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/25 21:37:30 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void draw_map(t_sdl *sdl, unsigned int *map)
{
	t_point *m = (t_point *)sdl->map->cont;

	size_t i = 0;

	while (i < sdl->map->len - 1)
	{
		if (m[i].h == 1)
		{
			((unsigned int *)map)[i / sdl->map->offset * 7 + i % sdl->map->offset] = 0xFFFFFF;
		}
		if (((unsigned int *)map)[(int)i] == 0x00FF00 || ((unsigned int *)map)[(int)i] == 0xFFFF00)
			map[i] = 0;
		i++;
	}
	printf("%f %zu %d\n",sdl->cam.angle, sdl->map->len / sdl->map->offset / 12 , sdl->cam.y / BLOCK);
	float angle = sdl->cam.angle;
	while (angle < 0.0)
		angle += 2 * M_PI;
	while (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	printf("%f\n", angle);
	((unsigned int *)map)[sdl->cam.y / BLOCK * sdl->map->len / sdl->map->offset / 12 + sdl->cam.x / BLOCK ] = 0xFFFF00;

	if (angle  < 1.57)
		((unsigned int *)map)[(sdl->cam.y / BLOCK) * sdl->map->len / sdl->map->offset / 12 + sdl->cam.x / BLOCK + 1] = 0x00FF00;
	else if (angle  < 3.14)
		((unsigned int *)map)[(sdl->cam.y / BLOCK - 1) * sdl->map->len / sdl->map->offset / 12 + sdl->cam.x / BLOCK ] = 0x00FF00;
	else if (angle < 4.71)
		((unsigned int *)map)[(sdl->cam.y / BLOCK) * sdl->map->len / sdl->map->offset / 12 + sdl->cam.x / BLOCK - 1] = 0x00FF00;
	else
		((unsigned int *)map)[(sdl->cam.y / BLOCK + 1) * sdl->map->len / sdl->map->offset / 12 + sdl->cam.x / BLOCK ] = 0x00FF00;
}
