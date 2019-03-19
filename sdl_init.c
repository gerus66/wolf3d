/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:10:19 by bturcott          #+#    #+#             */
/*   Updated: 2019/03/20 00:27:40 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_sdl.h"


void draw_texture(t_sdl *sdl)
{
    SDL_Rect params;

    params.h = 100;
    params.w = 100;
    params.x = 200;
    params.y = 200;
    SDL_Texture *one = SDL_CreateTextureFromSurface(sdl->render ,SDL_LoadBMP("textures/afrormosia.bmp"));
    SDL_Texture *two = SDL_CreateTextureFromSurface(sdl->render ,SDL_LoadBMP("textures/clouds1_east.bmp"));
    SDL_RenderCopy(sdl->render, one, NULL, &params);
    SDL_RenderPresent(sdl->render);
}

t_sdl *init_sdl(void)
{
    t_sdl *sdl;

    if (!(sdl = (t_sdl *)malloc(sizeof(t_sdl))))
        return (0);
    SDL_Init(SDL_INIT_EVERYTHING);
    sdl->window = SDL_CreateWindow("Wolf3D", 500, 500, 1000, 1000, SDL_WINDOW_RESIZABLE);
    sdl->render = SDL_CreateRenderer(sdl->window, -1, 2);
    sdl->text = SDL_CreateTexture(sdl->render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 1000, 1000);
    SDL_SetRenderTarget(sdl->render, sdl->text);
    return (sdl);    
}

void sdl_loop(t_sdl *sdl)
{
    int quit;
    SDL_Event e;
    
    quit = 0;
    while (quit == 0)
    {
        if (SDL_PollEvent(&e))
        {   draw_texture(sdl);
            SDL_PumpEvents();
                if (e.key.keysym.scancode == 41)
                   quit = 1;
        }
    }
}



int main (void)
{
    t_sdl *sdl = init_sdl();
    draw_texture(sdl);
    return (0);
}