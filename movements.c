/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:07:14 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/24 16:07:55 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		movements(t_sdl *sdl, int key, float ang)
{
	char	yfl;
	char	xfl;
	int		x;
	int		y;

	xfl = 1;
	yfl = 1;
	if (!(key == UP || key == DOWN || key == LEFT || key == RIGHT))
		return ;
	ang += (key == DOWN) ? M_PI : 0;
	ang += (key == LEFT) ? M_PI * 0.5 : 0;
	ang += (key == RIGHT) ? M_PI * 1.5 : 0;
	y = (float)sdl->cam.y - ((float)MOV_STEP * 2.0 * sin(ang));
	x = (float)sdl->cam.x + ((float)MOV_STEP * 2.0 * cos(ang));
	if (x <= 0 || x >= MAP_W(sdl->map) * BLOCK ||
			MAP(sdl->map)[MAP_W(sdl->map) * (sdl->cam.y / BLOCK) + x / BLOCK].h)
		xfl = 0;
	if (y <= 0 || y >= MAP_H(sdl->map) * BLOCK ||
			MAP(sdl->map)[MAP_W(sdl->map) * (y / BLOCK) + sdl->cam.x / BLOCK].h)
		yfl = 0;
	if (xfl)
		sdl->cam.x += (int)((float)MOV_STEP * cos(ang));
	if (yfl)
		sdl->cam.y -= (int)((float)MOV_STEP * sin(ang));
	if (!xfl || !yfl)
		sounds_control_panel(sdl->samples, 3);
}
