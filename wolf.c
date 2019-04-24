/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:10:19 by bturcott          #+#    #+#             */
/*   Updated: 2019/04/24 16:11:38 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void				rotations(t_sdl *sdl, SDL_Event e)
{
	if (e.motion.type == SDL_MOUSEMOTION && sdl->flags[2])
	{
		if (e.motion.yrel > 2 && sdl->cam.horiz > 5 * MOV_STEP)
			sdl->cam.horiz -= 2 * MOV_STEP;
		else if (e.motion.yrel < -2 && sdl->cam.horiz < WIN_H - 5 * MOV_STEP)
			sdl->cam.horiz += 2 * MOV_STEP;
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

static void				sdl_loop(t_sdl *sdl)
{
	SDL_Event e;

	while (1)
	{
		if (SDL_PollEvent(&e))
		{
			rotations(sdl, e);
			if (e.key.type == SDL_KEYDOWN || e.type == SDL_QUIT)
			{
				sounds(sdl, e);
				movements(sdl, e.key.keysym.scancode, sdl->cam.angle);
				if (e.key.keysym.scancode == 41 || e.type == SDL_QUIT)
					exit(clean_all(sdl, ""));
				if (e.key.keysym.scancode == SWITCH_MAP)
					sdl->flags[0] = sdl->flags[0] ? 0 : 1;
				if (e.key.keysym.scancode == SWITCH_TEXT)
					sdl->flags[1] = sdl->flags[1] ? 0 : 1;
				if (e.key.keysym.scancode == SWITCH_MOUSE)
					sdl->flags[2] = sdl->flags[2] ? 0 : 1;
			}
			reprint_all(sdl);
		}
	}
}

static SDL_Texture		**load_textures(t_sdl *sdl)
{
	SDL_Texture **texts;

	if (!(texts = ft_memalloc(sizeof(SDL_Texture *) * 4)))
		exit(clean_all(sdl, "Malloc fail\n"));
	if (!(texts[0] = SDL_CreateTextureFromSurface(sdl->render,
					SDL_LoadBMP("textures/1.bmp"))))
		exit(clean_all(sdl, "Texture loading fail\n"));
	if (!(texts[1] = SDL_CreateTextureFromSurface(sdl->render,
					SDL_LoadBMP("textures/2.bmp"))))
		exit(clean_all(sdl, "Texture loading fail\n"));
	if (!(texts[2] = SDL_CreateTextureFromSurface(sdl->render,
					SDL_LoadBMP("textures/3.bmp"))))
		exit(clean_all(sdl, "Texture loading fail\n"));
	if (!(texts[3] = SDL_CreateTextureFromSurface(sdl->render,
					SDL_LoadBMP("textures/4.bmp"))))
		exit(clean_all(sdl, "Texture loading fail\n"));
	return (texts);
}

static void				init_sdl(t_sdl *sdl)
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
	if (!(sdl->mapa = SDL_CreateTexture(sdl->render, TXT_FORMAT, TXT_ACCESS,
					sdl->map->offset * 30, MAP_H(sdl->map) * 30)))
		exit(clean_all(sdl, "Cant create the map\n"));
	sdl->texture_pack = load_textures(sdl);
	if (!(sdl->floor = SDL_LoadBMP("textures/floor.bmp")))
		exit(clean_all(sdl, "No Floor texture"));
	sdl->floor = SDL_ConvertSurfaceFormat(sdl->floor, TXT_FORMAT, 0);
	sdl->flags[0] = 0;
	sdl->flags[1] = 0;
	sdl->flags[2] = 0;
}

int						main(int argc, char **argv)
{
	t_sdl	sdl;
	int		fd;

	sdl.cam.x = 50;
	sdl.cam.y = 300;
	sdl.cam.angle = 0.0;
	sdl.cam.horiz = WIN_H / 2;
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
