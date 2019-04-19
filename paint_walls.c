/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:57:27 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/19 16:58:16 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void 	convert_texture(SDL_Texture *texture, SDL_Rect position,
									SDL_Rect *object, int offset)
{
	SDL_Rect curr;
	SDL_QueryTexture(texture, NULL, NULL, &curr.w, &curr.h);
	object->x = offset * (curr.w / BLOCK);
	object->w = curr.w / BLOCK;
	object->h = curr.h;
	object->y = 0;
}

/*
** params[0] - h (height of wall)
**       [1] - x (column of pixles in window)
**       [2] - offset_x (column of pixels in texture)
**       [3] - n (which texture use from pack)
*/

void			paint_walls(t_sdl *sdl, int *params)
{
	SDL_Rect texture;
	SDL_Rect object;
	
	if (params[3] == -1)
		return ;
	texture.h = 2 * params[0];
	texture.w = 2;
	texture.x = params[1];
	texture.y = sdl->cam.horiz - params[0];
	convert_texture(sdl->texture_pack[params[3]], texture, &object, params[2]);
	SDL_RenderCopy(sdl->render, sdl->texture_pack[params[3]], &object,
			&texture);		
}

/*
** params[0] - x (coord of pixel in window)
**       [1] - y (coord of pixel in window)
**       [2] - offset_x (coord of pixel in texture)
**       [3] - offset_y (coord of pixel in texture)
*/
/*
void			paint_floor(t_sdl *sdl, int *params)
{
	SDL_Rect texture;
	SDL_Rect object;
	
//	if (params[3] == -1)
//		return ;
	texture.h = 2;
	texture.w = 2;
	texture.x = params[0];
	texture.y = params[1];
	convert_texture(sdl->texture_pack[1], texture, &object, params[2]);
	SDL_RenderCopy(sdl->render, sdl->texture_pack[params[3]], &object,
			&texture);		
}*/
