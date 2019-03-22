/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/22 13:16:55 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	work_map(t_sdl *sbox, unsigned int *map, int len)
{
	int		i;
	int		map_size;
	t_point	*cp;

	i = -1;
	map_size = sbox->map->len / sizeof(t_point);
	cp = (t_point *)sbox->map->cont;
	printf("%f, %f\n", STEP, DIST);
	while (++i < len * WIN_H)
	{
		map[i] = 0x00FF;
//		if (cp[i].h)
//	    	map[100500 + i % sbox->map->offset + i / sbox->map->offset * len] = 0x42F4AD;
//		else
//			map[100500 + i % sbox->map->offset + i / sbox->map->offset * len] = 0xFFFFFF;
	}
}

void	work_it(t_sdl *sbox)
{
	sbox->cam.x = 500;
	sbox->cam.y = 500;
	sbox->cam.angle = 90;

	int	cam_r = sbox->cam.x / BLOCK;
	int	cam_c = sbox->cam.y / BLOCK;

	float xa = BLOCK / tan(sbox->cam.angle);
	int i = cam_r;
	while (i-- >= 0)
		if (sbox->map[cam_c + xa])


}
