/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:10:19 by bturcott          #+#    #+#             */
/*   Updated: 2019/03/24 15:28:47 by bturcott         ###   ########.fr       */
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

int		clean_all(t_sdl *sdl, char *msg)
{
	free(sdl->map);
	SDL_DestroyTexture(sdl->text);
	SDL_DestroyRenderer(sdl->render);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	write(1, msg, ft_strlen(msg));
	return (0);
}


static void		reprint_all(t_sdl *sdl)
{
	void *pixels;
	void *mappix;
	int pitch;
	

	SDL_SetRenderTarget(sdl->render, sdl->plane);

	SDL_LockTexture(sdl->mapa, NULL, (void **)&mappix, &pitch);
	SDL_LockTexture(sdl->text, NULL, (void **)&pixels, &pitch);
	work_it(sdl, (unsigned int *)pixels, pitch / sizeof(int));
	SDL_UnlockTexture(sdl->text);
	SDL_UnlockTexture(sdl->mapa);

	SDL_RenderClear(sdl->render);
	SDL_RenderCopy(sdl->render, sdl->text, 0, &(SDL_Rect){0, 0, WIN_W, WIN_H});
	if (sdl->flags[0])
	{
		draw_map(sdl, (unsigned int *)mappix);
		SDL_RenderCopy(sdl->render, sdl->mapa, 0, &(SDL_Rect){30, WIN_H / 3 * 2,
				sdl->map->offset * WIN_W / 30 , 
				sdl->map->len / sdl->map->offset / 12 * WIN_H / 30});
	}
	SDL_SetRenderTarget(sdl->render, NULL);
	SDL_RenderPresent(sdl->render);
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
					sdl->map->offset, sdl->map->len / sdl->map->offset / 12)))
		exit(clean_all(sdl, "Cant create the map\n"));
	sdl->flags[0] = 0;
}

static void		sdl_loop(t_sdl *sdl)
{
	SDL_Event e;

	while (1)
	{
		if (SDL_PollEvent(&e))
		{   
			printf("%d\n", e.key.keysym.scancode);
			if (e.key.keysym.scancode == 41 || e.quit.type == SDL_QUIT)
				exit(clean_all(sdl, "exit on esc or red cross\n"));
			else if (e.key.keysym.scancode == 79)
				sdl->cam.angle -= M_PI / 32;
			else if (e.key.keysym.scancode == 80)
				sdl->cam.angle += M_PI / 32;
			else if (e.key.keysym.scancode == 26)
			{
				sdl->cam.y += 5 * round(sin(sdl->cam.angle) * 100) / 100;
				sdl->cam.x += 5 * round(cos(sdl->cam.angle) * 100) / 100;
			}
			else if (e.key.keysym.scancode == 22)
			{
				sdl->cam.y += 5 * round(sin(sdl->cam.angle + M_PI) * 100) / 100;
				sdl->cam.x += 5 * round(cos(sdl->cam.angle + M_PI) * 100) / 100;
			}
			else if (e.key.keysym.scancode == 4)
			{
				sdl->cam.y += 5 * round(sin(sdl->cam.angle + M_PI * 3 / 2) * 100) / 100;
				sdl->cam.x += 5 * round(cos(sdl->cam.angle + M_PI * 3 / 2) * 100) / 100;
			}
			else if (e.key.keysym.scancode == 7)
			{
				sdl->cam.y += 5 * round(sin(sdl->cam.angle + M_PI / 2) * 100) / 100;
				sdl->cam.x += 5 * round(cos(sdl->cam.angle + M_PI / 2) * 100) / 100;
			}
			
			else if (e.key.keysym.scancode == 16 && e.key.type == SDL_KEYDOWN
					&& !sdl->flags[0])
				sdl->flags[0] = 1;
			else if (e.key.keysym.scancode == 16 && e.key.type == SDL_KEYDOWN
					&& sdl->flags[0])
				sdl->flags[0] = 0;
				printf("x-> %d y-> %d cos-> %f sin-> %f\n", sdl->cam.x, sdl->cam.y, cos(sdl->cam.angle), sin(sdl->cam.angle));
			reprint_all(sdl);
		}
	}
}



int				main(int argc, char **argv)
{
	t_sdl 	sdl;
	int		fd;

	sdl.cam.x = 200;
	sdl.cam.y = 200;
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
