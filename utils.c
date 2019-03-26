/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:33:54 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/25 20:34:43 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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


void		reprint_all(t_sdl *sdl)
{
	void *pixels;
	void *mappix;
	int pitch;


	SDL_SetRenderTarget(sdl->render, sdl->plane);

	SDL_LockTexture(sdl->mapa, NULL, (void **)&mappix, &pitch);
	SDL_LockTexture(sdl->text, NULL, (void **)&pixels, &pitch);
	cast_walls(sdl, (unsigned int *)pixels);
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