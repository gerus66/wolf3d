/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:42:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/24 12:38:25 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define N 0x42F4AD
#define E 0x8A6DA3
#define W 0xBD76F7
#define S 0xF44262
#define SKY 0xA3F8FF
#define FLOOR 0x9E9380

static float	first_shift_x(float ang, int bound, int x, int y)
{
	if (QT_12(ang))
		bound++;
	if (QT_14(ang))
		return ((float)x + ((float)y - bound * BLOCK) / tan(ang));
	else
		return ((float)x - ((float)y - bound * BLOCK) / tan(M_PI - ang));
}

static float	first_shift_y(float ang, int bound, int x, int y)
{
	if (QT_23(ang))
	{
		bound++;
		ang = ang - M_PI;
	}
	if (QT_12(ang))
		return ((float)y - (bound * BLOCK - (float)x) * tan(ang));
	else
		return ((float)y + ((float)x - bound * BLOCK) * tan(ang));
}

static float	get_dist_x(t_sdl *sbox, float ang, char *fl, int *offset)
{
	int		next_r;
	int		cur_c;
	float	xa;
	float	x;

	next_r = (QT_12(ang)) ? sbox->cam.y / BLOCK - 1 : sbox->cam.y / BLOCK + 1;
	xa = fabs(BLOCK / tan((QT_14(ang)) ? ang : M_PI - ang));
	x = first_shift_x(ang, next_r, sbox->cam.x, sbox->cam.y);
	cur_c = (int)x / BLOCK;
	while (1)
	{
		if ((cur_c >= MAP_W(sbox->map) || x < 0 ||
			next_r >= MAP_H(sbox->map) || next_r <= -1) ||
			(MAP(sbox->map)[sbox->map->offset * next_r + cur_c].h && (*fl = 1)))
		{
			*offset = (int)x;
			return (sqrt(pow(sbox->cam.y -
				(QT_12(ang) ? next_r + 1 : next_r) * BLOCK, 2) +
				pow(sbox->cam.x - x, 2)));
		}
		next_r = (QT_12(ang)) ? next_r - 1 : next_r + 1;
		x = (QT_14(ang)) ? x + xa : x - xa;
		cur_c = (int)x / BLOCK;
	}
	return (0.0);
}

static float	get_dist_y(t_sdl *sbox, float ang, char *fl, int *offset)
{
	int		cur_r;
	int		next_c;
	float	ya;
	float	y;

	next_c = (QT_14(ang)) ? sbox->cam.x / BLOCK + 1 : sbox->cam.x / BLOCK - 1;
	ya = fabs(BLOCK * tan((QT_14(ang)) ? ang : M_PI - ang));
	y = first_shift_y(ang, next_c, sbox->cam.x, sbox->cam.y);
	cur_r = (int)y / BLOCK;
	while (1)
	{
		if ((cur_r >= MAP_H(sbox->map) || y < 0 ||
			next_c >= MAP_W(sbox->map) || next_c <= -1) ||
			(MAP(sbox->map)[sbox->map->offset * cur_r + next_c].h && (*fl = 1)))
		{
			*offset = (int)y;
			return (sqrt(pow(sbox->cam.x -
					(QT_23(ang) ? next_c + 1 : next_c) * BLOCK, 2) +
					pow(sbox->cam.y - y, 2)));
		}
		next_c = QT_14(ang) ? next_c + 1 : next_c - 1;
		y = QT_12(ang) ? y - ya : y + ya;
		cur_r = (int)y / BLOCK;
	}
	return (0.0);
}

static float	get_height(t_sdl *sbox, float ang, int *offset, char *fl)
{
	char	ya_fl;
	int		ya_offset;
	float	dist;
	float	disty;

	dist = get_dist_x(sbox, ang, fl, offset);
	ya_fl = 0;
	ya_offset = 0;
	disty = get_dist_y(sbox, ang, &ya_fl, &ya_offset);
	if (!(*fl) && !ya_fl && (*fl = 's'))
		return (WALL_H * DIST / (disty < dist ? disty : dist)
				/ cos(ang - sbox->cam.angle));
	else
	{
		if ((ya_fl && disty < dist) || !(*fl))
		{
			*offset = ya_offset;
			*fl = 'y';
			dist = disty;
		}
		else
			*fl = 'x';
		return (WALL_H * DIST / dist / cos(ang - sbox->cam.angle));
	}
}

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

//	int fl = 0;
//	if (*off_y > 340 && *off_y < 360)
//		fl = 1;
	dist = CAM_H * DIST / ABS(*off_y - sbox->cam.horiz) /
		cos(ang - sbox->cam.angle);
	coef = sbox->floor->w / BLOCK;
	
	*off_y = (int)(dist * (QT_12(ang) ? sin(ang) : -sin(ang)) * coef);
	if (*off_y <= sbox->floor->w)
		*off_y += sbox->floor->w;
	*off_y -= QT_12(ang) ? sbox->cam.y * coef % sbox->floor->w
				: sbox->floor->w - sbox->cam.y * coef % sbox->floor->w;
	*off_y =  QT_12(ang) ? sbox->floor->w - *off_y % sbox->floor->w :
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
//	if (fl)
//		printf("[%d %d] ", *off_x, *off_y);
}

/*
** params[0] - h (height of wall)
**       [1] - j (current y coord)
**       [2] - fl ('s' for just sky)
*/

static int		just_sky(t_sdl *sbox, int *param, float ang)
{
	int	off_x;
	int	off_y;
	Uint32 *p;

	if (param[1] >= sbox->cam.horiz + param[0] )
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

//	printf("map %d x %d \n", MAP_W(sbox->map), MAP_H(sbox->map));
//	printf("I m in [%d %d] looking at %d grad ", sbox->cam.x / BLOCK,
//			sbox->cam.y / BLOCK, (int)(sbox->cam.angle / M_PI * 180));
//	printf("(from %d to %d grad)\n",
//			(int)((sbox->cam.angle - FOV / 2) / M_PI * 180),
//			(int)((sbox->cam.angle + FOV / 2) / M_PI * 180));
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

static int select_text(float ang, char fl)
{
	if ((fl == 'x' && QT_12(ang)))
		return (0);
	if ((fl == 'x' && QT_34(ang)))
		return (1);
	if ((fl == 'y' && QT_23(ang)))
		return (2);
	if ((fl == 'y' && QT_14(ang)))
		return (3);
	return (-1);
}

void			texts_to_render(t_sdl *sbox, float ang)
{
	int		i;
	int		j;
	int		h;
	char	fl;
	int		offset;

//	printf("map %d x %d \n", MAP_W(sbox->map), MAP_H(sbox->map));
//	printf("I m in [%d %d] looking at %d grad ", sbox->cam.x / BLOCK,
//			sbox->cam.y / BLOCK, (int)(sbox->cam.angle / M_PI * 180));
//	printf("(from %d to %d grad)\n",
//			(int)((sbox->cam.angle - FOV / 2) / M_PI * 180),
//			(int)((sbox->cam.angle + FOV / 2) / M_PI * 180));
	i = -1;
	while (++i < WIN_W)
	{
		if (ang > M_PI)
			ang = -(2 * M_PI - ang);
		else if (ang < -M_PI)
			ang = 2 * M_PI + ang;
		fl = 0;
		offset = 0;
		h = get_height(sbox, ang, &offset, &fl);
		paint_walls(sbox, (int[]){h, i, offset % BLOCK, select_text(ang, fl)});
		ang -= STEP;
	}
}
