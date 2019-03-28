/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:33:54 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/28 12:25:57 by mbartole         ###   ########.fr       */
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


	SDL_RenderClear(sdl->render);
	SDL_LockTexture(sdl->text, NULL, (void **)&pixels, &pitch);
	pixels_to_render(sdl, (unsigned int *)pixels);
	SDL_RenderCopy(sdl->render, sdl->text, 0, &(SDL_Rect){0, 0, WIN_W, WIN_H});
	SDL_UnlockTexture(sdl->text);
	if (sdl->flags[1])
		texts_to_render(sdl);
	if (sdl->flags[0])
	{
		SDL_LockTexture(sdl->mapa, NULL, (void **)&mappix, &pitch);
		draw_map(sdl, (unsigned int *)mappix);
		SDL_UnlockTexture(sdl->mapa);
		SDL_RenderCopy(sdl->render, sdl->mapa, 0, &(SDL_Rect){30, WIN_H / 3 * 2,
				sdl->map->offset * 30,
				MAP_H(sdl->map) * 30});
	}
	SDL_RenderPresent(sdl->render);
}
