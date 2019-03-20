/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/20 23:09:51 by mbartole         ###   ########.fr       */
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
	while (++i < map_size)
	{
		if (cp[i].h)
	    	map[100500 + i % sbox->map->offset + i / sbox->map->offset * len] = 0x42F4AD;
		else
			map[100500 + i % sbox->map->offset + i / sbox->map->offset * len] = 0xFFFFFF;
	}
}
