/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:31:26 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/25 15:11:57 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#define LINES_COS1(x) (-1 * cos(x + 210))
#define LINES_SIN1(x) (1 * sin(x + 210))
#define LINES_COS2(x) (-1 * cos(x + 60))
#define LINES_SIN2(x) (1 * sin(x + 60))

int		draw_lines_iter(int *c, float *iters, int offs, unsigned int *map)
{
	int it2;

	it2 = c[2];
	if (map[(offs * 30 * (int)(iters[1] + c[1] + it2 * cos(iters[5] + 90))) \
	+ (int)(iters[0] + c[0] + it2 * sin(iters[5] + 90))] == 0xFFFFFF \
	|| map[(offs * 30 * (int)(iters[3] + c[1] - it2 * cos(iters[5] \
	+ 180))) + (int)(iters[2] + c[0] - it2 * sin(iters[5] + 180))] == 0xFFFFFF)
		return (0);
	if (map[(offs * 30 * (int)(iters[1] + c[1])) + (int)(iters[0] \
		+ c[0])] == 0xFFFFFF || map[(offs * 30 * (int)(iters[3] + \
		c[1])) + (int)(iters[2] + c[0])] == 0xFFFFFF)
		return (0);
	map[(offs * 30 * (int)(iters[1] + (float)c[1]))\
	+ (int)(iters[0] + (float)c[0])] = 0x00FFFF;
	map[(offs * 30 * (int)(iters[3] + (float)c[1]))\
	+ (int)(iters[2] + (float)c[0])] = 0x00FFFF;
	return (1);
}

void	draw_player(int *c, float ang, unsigned int *map, int offs)
{
	float		it[6];
	int			it2;

	ft_bzero((void *)it, 6 * sizeof(float));
	it[5] = ang;
	while (c[2]++ < 100)
	{
		if (!(draw_lines_iter(c, it, offs, map)))
			break ;
		it2 = (int)c[2];
		while (it2 <= 30 && it2 >= 10 && it2--)
		{
			map[(offs * 30 * (int)(it[1] + (float)c[1] + it2 * cos(ang + 90))) \
			+ (int)(it[0] + (float)c[0] + it2 * sin(ang + 90))] = 0xFFF00F;
			map[(offs * 30 * (int)(it[3] + c[1] - it2 * cos(ang + 180))) \
			+ (int)(it[2] + (float)c[0] - it2 * sin(ang + 180))] = 0xFFF00F;
			if (it2 < 10)
				break ;
		}
		it[0] += LINES_COS1(ang);
		it[1] += LINES_SIN1(ang);
		it[2] += LINES_COS2(ang);
		it[3] += LINES_SIN2(ang);
	}
}

void	draw_a_block(int *c, t_sdl *sdl, unsigned int *map, char type)
{
	int y;
	int x;

	if (type == 'w')
	{
		c[0] *= 30;
		y = c[0] + 30;
		x = c[1] * 30 + 30;
		while (c[0] < y)
		{
			c[1] = x - 30;
			while (c[1] < x)
			{
				map[sdl->map->offset * 30 * c[0] + c[1]] = 0xFFFFFF;
				c[1]++;
			}
			c[0]++;
		}
	}
	else
	{
		draw_player((int[]){sdl->cam.x * 30 / BLOCK, sdl->cam.y * 30 \
		/ BLOCK, 0}, sdl->cam.angle, map, sdl->map->offset);
	}
}

void	draw_map(t_sdl *sdl, unsigned int *map)
{
	t_point	*m;
	int		i;

	i = 0;
	m = (t_point *)sdl->map->cont;
	while (i++ < MAP_H(sdl->map) * sdl->map->offset * 900)
		if (i < MAP_W(sdl->map) * 30 || (i) % (MAP_W(sdl->map) * 30) \
		== 0 || i / MAP_W(sdl->map) == MAP_H(sdl->map) - 10 || \
		(i + 1) % (MAP_W(sdl->map) * 30) == 0)
			((unsigned int *)map)[i] = 0xFFFFFF;
		else
			((unsigned int *)map)[i] = 0x0;
	i = -1;
	while (++i < sdl->map->offset * MAP_H(sdl->map))
	{
		if (m[i].h)
		{
			draw_a_block((int[2]){i / sdl->map->offset, \
			i % sdl->map->offset}, sdl, map, 'w');
		}
	}
	draw_a_block((int[2]){sdl->cam.x, sdl->cam.y}, sdl, map, 'p');
}
