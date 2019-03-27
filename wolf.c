/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:10:19 by bturcott          #+#    #+#             */
/*   Updated: 2019/03/27 18:48:30 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		rotations(t_sdl *sdl, SDL_Event e)
{
	if (e.motion.type == SDL_MOUSEMOTION)
	{
		if (e.motion.xrel > 0)	
			sdl->cam.angle -= ROT_STEP;
		else if (e.motion.xrel < 0)
			sdl->cam.angle += ROT_STEP;
		if (sdl->cam.angle > M_PI)
			sdl->cam.angle -= 2 * M_PI;
		else if (sdl->cam.angle < -M_PI)
			sdl->cam.angle += 2 * M_PI;
	}
	if (e.key.keysym.scancode == 79 || e.key.keysym.scancode == 80)
	{
		if (e.key.keysym.scancode == 79)	
			sdl->cam.angle -= ROT_STEP;
		else
			sdl->cam.angle += ROT_STEP;
		if (sdl->cam.angle > M_PI)
			sdl->cam.angle -= 2 * M_PI;
		else if (sdl->cam.angle < -M_PI)
			sdl->cam.angle += 2 * M_PI;
	}
}

static void		movements(t_sdl *sdl, SDL_Event e)
{
	if (e.key.keysym.scancode == 26)
	{
		sdl->cam.y -= MOV_STEP * round(sin(sdl->cam.angle) * 100) / 100;
		sdl->cam.x += MOV_STEP * round(cos(sdl->cam.angle) * 100) / 100;
	}
	else if (e.key.keysym.scancode == 22)
	{
		sdl->cam.y -= MOV_STEP * round(sin(sdl->cam.angle + M_PI) * 100) / 100;
		sdl->cam.x += MOV_STEP * round(cos(sdl->cam.angle + M_PI) * 100) / 100;
	}
	else if (e.key.keysym.scancode == 4)
	{
		sdl->cam.y += MOV_STEP * round(sin(sdl->cam.angle + M_PI * 3 / 2) * 100) / 100;
		sdl->cam.x -= MOV_STEP * round(cos(sdl->cam.angle + M_PI * 3 / 2) * 100) / 100;
	}
	else if (e.key.keysym.scancode == 7)
	{
		sdl->cam.y += MOV_STEP * round(sin(sdl->cam.angle + M_PI / 2) * 100) / 100;
		sdl->cam.x -= MOV_STEP * round(cos(sdl->cam.angle + M_PI / 2) * 100) / 100;
	}
}

static void		sdl_loop(t_sdl *sdl)
{
	SDL_Event e;

	while (1)
	{
		if (SDL_PollEvent(&e))
		{
			printf("%d\n", e.key.keysym.scancode);
			rotations(sdl, e);
			movements(sdl, e);
			if (e.key.keysym.scancode == 41 || e.quit.type == SDL_QUIT)
				exit(clean_all(sdl, "exit on esc or red cross\n"));
			else if (e.key.keysym.scancode == 16 && e.key.type == SDL_KEYDOWN
					&& !sdl->flags[0])
				sdl->flags[0] = 1;
			else if (e.key.keysym.scancode == 16 && e.key.type == SDL_KEYDOWN
					&& sdl->flags[0])
				sdl->flags[0] = 0;
			else if (e.key.keysym.scancode == 23 && e.key.type == SDL_KEYDOWN
					&& !sdl->flags[1])
				sdl->flags[1] = 1;
			else if (e.key.keysym.scancode == 23 && e.key.type == SDL_KEYDOWN
					&& sdl->flags[1])
				sdl->flags[1] = 0;
		//	printf("x-> %d y-> %d cos-> %f sin-> %f\n", sdl->cam.x, sdl->cam.y, cos(sdl->cam.angle), sin(sdl->cam.angle));
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
		exit(clean_all(sdl, "Cant create the map\n"));
		//printf("%zu %d\n", sdl->map->offset, MAP_H(sdl->map));
	if (!(sdl->texture_pack = load_textures(sdl)))
		ft_putendl("No Textures");
	sdl->flags[0] = 0;
	sdl->flags[1] = 0;
}

int				main(int argc, char **argv)
{
	t_sdl 	sdl;
	int		fd;

	sdl.cam.x = 100;
	sdl.cam.y = 300;
	sdl.cam.angle = (float)M_PI / 2;
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
	sdl_loop(&sdl);

	return (0);
}
