/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/24 15:10:12 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define N 0x42F4AD
#define E 0x8A6DA3
#define W 0xBD76F7
#define S 0xF44262
#define SKY 0xA3F8FF
#define FLOOR 0x9E9380

/*
** param: {h, j, horiz}
*/

static int		all_color(float ang, int *param, char fl)
{
	if (param[1] >= param[2] + param[0])
		return (FLOOR);
	if (param[1] < param[2] - param[0] ||
		(fl == 's' && param[1] < param[2] + param[0]))
		return (SKY);
	if ((fl == 'x' && QT_12(ang)))
		return (N);
	if ((fl == 'x' && QT_34(ang)))
		return (S);
	if ((fl == 'y' && QT_23(ang)))
		return (W);
	if ((fl == 'y' && QT_14(ang)))
		return (E);
	return (0xFFFFFF);
}

static void		get_floor_offset(t_sdl *sbox, float ang, int *off_x, int *off_y)
{
	float	dist;
	int		coef;

	dist = 2 * CAM_H * DIST / ABS(*off_y - sbox->cam.horiz) /
		cos(ang - sbox->cam.angle);
	coef = sbox->floor->w / BLOCK;
	*off_y = (int)(dist * (QT_12(ang) ? sin(ang) : -sin(ang)) * coef);
	if (*off_y <= sbox->floor->w)
		*off_y += sbox->floor->w;
	*off_y -= QT_12(ang) ? sbox->cam.y * coef % sbox->floor->w
				: sbox->floor->w - sbox->cam.y * coef % sbox->floor->w;
	*off_y = QT_12(ang) ? sbox->floor->w - *off_y % sbox->floor->w :
		*off_y % sbox->floor->w;
	if (*off_y == sbox->floor->w)
		*off_y = 0;
	*off_x = (int)(dist * (QT_14(ang) ? cos(ang) : -cos(ang)) * coef);
	if (*off_x <= sbox->floor->w)
		*off_x += sbox->floor->w;
	*off_x -= QT_14(ang) ? sbox->floor->w - sbox->cam.x * coef % sbox->floor->w
				: sbox->cam.x * coef % sbox->floor->w;
	*off_x = QT_14(ang) ? *off_x % sbox->floor->w :
		sbox->floor->w - *off_x % sbox->floor->w;
	if (*off_x == sbox->floor->w)
		*off_x = 0;
}

/*
** params[0] - h (height of wall)
**       [1] - j (current y coord)
**       [2] - fl ('s' for just sky)
*/

static int		just_sky(t_sdl *sbox, int *param, float ang)
{
	int		off_x;
	int		off_y;
	Uint32	*p;

	if (param[1] >= sbox->cam.horiz + param[0])
	{
		off_y = param[1];
		get_floor_offset(sbox, ang, &off_x, &off_y);
		p = (Uint32 *)(sbox->floor->pixels);
		return (p[off_y * sbox->floor->w + off_x]);
	}
	if (param[1] < sbox->cam.horiz - param[0] ||
			(param[2] == 's' && param[1] < sbox->cam.horiz + param[0]))
		return (SKY);
	return (0xFFFFFF);
}

void			pixels_to_render(t_sdl *sbox, unsigned int *map, float ang)
{
	int		i;
	int		j;
	int		h;
	char	fl;
	int		offset;

	i = -1;
	while (++i < WIN_W)
	{
		fit_angle(&ang);
		fl = 0;
		offset = 0;
		h = get_height(sbox, ang, &offset, &fl);
		j = -1;
		while (++j < WIN_H)
			map[i + j * WIN_W] = sbox->flags[1] ?
				just_sky(sbox, (int[]){h, j, fl}, ang) :
				all_color(ang, (int[]){h, j, sbox->cam.horiz}, fl);
		ang -= STEP;
	}
}
