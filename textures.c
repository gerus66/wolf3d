/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 08:18:53 by bturcott          #+#    #+#             */
/*   Updated: 2019/03/22 19:26:16 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

// void    place_texture(t_cast *cast, t_sdl *sdl)
// {
//     int i;

//     i = (int)cast->cam.angle / 90.0;
//     SDL_RenderCopy(sdl->render, cast->tex.textures[i], NULL, &cast->tex.pos);
// }

// SDL_Texture             **load_textures(t_sdl *sdl)
// {
//     SDL_Texture **texts;

//     if (!(texts = ft_memalloc(sizeof(SDL_Texture *) * 4)))
//         return (0);
//     if (!(texts[0] = SDL_CreateTextureFromSurface(sdl->render, SDL_LoadBMP("textures/1.bmp"))))
//         exit(clean_all(sdl, "Texture loading fail\n"));
//     if (!(texts[1] = SDL_CreateTextureFromSurface(sdl->render, SDL_LoadBMP("textures/2.bmp"))))
//         exit(clean_all(sdl, "Texture loading fail\n"));
//     if (!(texts[2] = SDL_CreateTextureFromSurface(sdl->render, SDL_LoadBMP("textures/3.bmp"))))
//         exit(clean_all(sdl, "Texture loading fail\n"));
//     if (!(texts[3] = SDL_CreateTextureFromSurface(sdl->render, SDL_LoadBMP("textures/4.bmp"))))
//         exit(clean_all(sdl, "Texture loading fail\n"));
//     return (texts);
// }
