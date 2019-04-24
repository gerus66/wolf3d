/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:57:27 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/24 15:10:01 by mbartole         ###   ########.fr       */
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

static int		select_text(float ang, char fl)
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
