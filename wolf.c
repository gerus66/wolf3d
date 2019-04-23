/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:10:19 by bturcott          #+#    #+#             */
/*   Updated: 2019/04/23 19:14:47 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		rotations(t_sdl *sdl, SDL_Event e)
{
	if (e.motion.type == SDL_MOUSEMOTION && sdl->flags[2])
	{
		if (e.motion.yrel > 2 && sdl->cam.horiz > 5 * MOV_STEP)
			sdl->cam.horiz -= MOV_STEP;
		else if (e.motion.yrel < -2 && sdl->cam.horiz < WIN_H - 5 * MOV_STEP)
			sdl->cam.horiz += MOV_STEP;
		if (e.motion.xrel > 5)	
			sdl->cam.angle -= ROT_STEP;
		else if (e.motion.xrel < -5)
			sdl->cam.angle += ROT_STEP;
		fit_angle(&(sdl->cam.angle));
	}
	if (e.key.keysym.scancode >= 79 && e.key.keysym.scancode <= 82)
	{
		if (e.key.keysym.scancode == 79)	
			sdl->cam.angle -= ROT_STEP;
		else if (e.key.keysym.scancode == 80)
			sdl->cam.angle += ROT_STEP;
		else if (e.key.keysym.scancode == 81 && sdl->cam.horiz > 5 * MOV_STEP)	
			sdl->cam.horiz -= MOV_STEP;
		else if (e.key.keysym.scancode == 82 &&
				sdl->cam.horiz < WIN_H - 5 * MOV_STEP)	
			sdl->cam.horiz += MOV_STEP;
		fit_angle(&(sdl->cam.angle));
	}
}

static void		movements(t_sdl *sdl, int key, float ang)
{
	char	fl;
	char	yfl;
	char	xfl;
	int		x;
	int		y;

	fl = 0;
	xfl = 1;
	yfl = 1;
	if (key == UP && (fl = 1))
		;
	else if (key == DOWN && (fl = 1))
		ang += M_PI;
	else if (key == LEFT && (fl = 1))
		ang += M_PI * 0.5;
	else if (key == RIGHT && (fl = 1))
		ang += M_PI * 1.5;
	if (fl)
	{
		y = sdl->cam.y - (int)((float)MOV_STEP * 2.0 * sin(ang));
		x = sdl->cam.x + (int)((float)MOV_STEP * 2.0 * cos(ang));
		if (x <= 0 || x >= MAP_W(sdl->map) * BLOCK ||
				MAP(sdl->map)[MAP_W(sdl->map) * (sdl->cam.y / BLOCK) + x / BLOCK].h)
			xfl = 0;
		if (y <= 0 || y >= MAP_H(sdl->map) * BLOCK ||
				MAP(sdl->map)[MAP_W(sdl->map) * (y / BLOCK) + sdl->cam.x / BLOCK].h)
			yfl = 0;
		if (xfl && yfl)
		{
			sdl->cam.x += (int)((float)MOV_STEP * cos(ang));
			sdl->cam.y -= (int)((float)MOV_STEP * sin(ang));
			return ;
		}
		if (!yfl)
		{
			printf("angle to wall %d\n",
				(int)(atan((float)(y - sdl->cam.y) / (float)(x - sdl->cam.x)) / M_PI * 180));
	//		if (x - sdl->cam.x > 0)
	//			movements(sdl, key,
	//				ang + fabs(atan2(y - sdl->cam.y, x - sdl->cam.x)));
	//		else
	//			movements(sdl, key,
	//				ang - fabs(atan2(y - sdl->cam.y, x - sdl->cam.x)));
			return ;
		}
	}
}

static void		sdl_loop(t_sdl *sdl)
{
	SDL_Event e;

	while (1)
	{
		if (SDL_PollEvent(&e))
		{
			rotations(sdl, e);
			printf("KEY %d\n", e.key.keysym.scancode);
			if (e.key.type == SDL_KEYDOWN)
			{
				movements(sdl, e.key.keysym.scancode, sdl->cam.angle);
				if (e.key.keysym.scancode == 41 || e.quit.type == SDL_QUIT)
					exit(clean_all(sdl, "exit on esc or red cross\n"));
				if (e.key.keysym.scancode == SWITCH_MAP)
					sdl->flags[0] = sdl->flags[0] ? 0 : 1;
				if (e.key.keysym.scancode == SWITCH_TEXT)
					sdl->flags[1] = sdl->flags[1] ? 0 : 1;
				if (e.key.keysym.scancode == SWITCH_MOUSE)
					sdl->flags[2] = sdl->flags[2] ? 0 : 1;
				printf("x-> %d y-> %d cos-> %f sin-> %f\n", sdl->cam.x,
					sdl->cam.y, cos(sdl->cam.angle), sin(sdl->cam.angle));
			}
			reprint_all(sdl);
		}
	}
}

static void		init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		exit(clean_all(sdl, "Cant initialize SDL\n"));
	if (!(sdl->window = SDL_CreateWindow(NAME, WIN_POS_X, WIN_POS_Y, WIN_W,
					WIN_H, WIN_FLAGS)))
		exit(clean_all(sdl, "Cant create window\n"));
	if (!(sdl->render = SDL_CreateRenderer(sdl->window, -1, REN_FLAGS)))
		exit(clean_all(sdl, "Cant create renderer\n"));
	if (!(sdl->text = SDL_CreateTexture(sdl->render, TXT_FORMAT, TXT_ACCESS,
					WIN_W, WIN_H)))
		exit(clean_all(sdl, "Cant create texture\n"));
	if (!(sdl->plane = SDL_CreateTexture(sdl->render, TXT_FORMAT, TXT_ACCESS,
					WIN_W, WIN_H)))
		exit(clean_all(sdl, "Cant create the plane\n"));
	if (!(sdl->mapa = SDL_CreateTexture(sdl->render, TXT_FORMAT, TXT_ACCESS,
					sdl->map->offset * 30, MAP_H(sdl->map) * 30)))
			//		sdl->map->offset, sdl->map->len / sdl->map->offset / 12)))
		exit(clean_all(sdl, "Cant create the map\n"));
	if (!(sdl->texture_pack = load_textures(sdl)))
		exit(clean_all(sdl, "No Textures\n"));
	if (!(sdl->floor = SDL_LoadBMP("textures/1.bmp")))
		exit(clean_all(sdl, "No Floor texture"));
	printf("floor w = %d, floor h = %d\n", sdl->floor->w, sdl->floor->h);
	sdl->flags[0] = 0;
	sdl->flags[1] = 0;
	sdl->flags[2] = 0;
}

int				main(int argc, char **argv)
{
	t_sdl 	sdl;
	int		fd;

	sdl.cam.x = 100;
	sdl.cam.y = 300;
	sdl.cam.angle = 0.0;
	sdl.cam.horiz = WIN_H / 2;
	printf("Distance to proj plane %d\n", (int)DIST);
	printf("View point on [%d, %d, %d] angle %.1f\n",
			sdl.cam.x, sdl.cam.y, CAM_H, sdl.cam.angle);
	printf("Step at angle is %.5f radian\n", STEP);
	printf("Height of wall %d\n", WALL_H);

	if (argc == 1 && (fd = open(MAP_DEFAULT, O_RDONLY)) == -1)
		return (clean_all(&sdl, "Cant open default map\n"));
	else if (argc == 2 && (fd = open(argv[1], O_RDONLY)) == -1)
		return (clean_all(&sdl, "Cant open custom map\n"));
	else if (argc > 2)
		return (clean_all(&sdl, USAGE));

	read_map(&sdl, fd);
	init_sdl(&sdl);
	init_music(&sdl);
	sdl_loop(&sdl);

	return (0);
}
