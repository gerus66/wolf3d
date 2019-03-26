/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 08:18:53 by bturcott          #+#    #+#             */
/*   Updated: 2019/03/26 12:42:29 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Texture             **load_textures(t_sdl *sdl)
{
    SDL_Texture **texts;

    if (!(texts = ft_memalloc(sizeof(SDL_Texture *) * 4)))
        return (NULL);
    if (!(texts[0] = SDL_CreateTextureFromSurface(sdl->render, SDL_LoadBMP("textures/1.bmp"))))
       return (NULL);
    if (!(texts[1] = SDL_CreateTextureFromSurface(sdl->render, SDL_LoadBMP("textures/2.bmp"))))
        return (NULL);
    if (!(texts[2] = SDL_CreateTextureFromSurface(sdl->render, SDL_LoadBMP("textures/3.bmp"))))
        return (NULL);
    if (!(texts[3] = SDL_CreateTextureFromSurface(sdl->render, SDL_LoadBMP("textures/4.bmp"))))
        return (NULL);
    return (texts);
}
