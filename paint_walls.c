/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:57:27 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/26 13:16:30 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

# define N 0x42F4AD
# define E 0x42D9F4
# define W 0xF4D742
# define S 0xF44262


void 	convert_texture(SDL_Texture *texture, SDL_Rect position, SDL_Rect *object, int offset)
{
	SDL_Rect curr;
	SDL_QueryTexture(texture, NULL, NULL, &curr.w, &curr.h);
	//printf("current == x-> %d y-> %d w-> %d h-> %d\n", curr.x, curr.y, curr.w, curr.h);
	object->x = offset * curr.w / BLOCK;
	object->w = 1;
	object->h = curr.h;
	object->y = 0;
	//position->w = curr.w % position->w;

}


int select_texture(float ang, char fl)
{
	if ((fl == 'x' && QT_12(ang)))
		return (0);
	if ((fl == 'x' && QT_34(ang)))
		return (1);
	if ((fl == 'y' && QT_23(ang)))
		return (2);
	if ((fl == 'y' && QT_14(ang)))
		return (3);
}

void		paint_walls(t_sdl *sdl, float ang, int *params, char side)
{
	//printf("%d\n", offset);
	SDL_Rect texture;
	SDL_Rect object;

	texture.h = WIN_H / 2 + params[0];
	texture.w = 1;
	texture.x = params[1];
	texture.y = WIN_H / 2 - params[0];
	convert_texture(sdl->texture_pack[1], texture, &object, params[2]);
	SDL_RenderCopy(sdl->render, sdl->texture_pack[1], &object, &texture);
}
