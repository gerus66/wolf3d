/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_sdl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:13:34 by bturcott          #+#    #+#             */
/*   Updated: 2019/03/19 21:56:53 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_SDL_H
# define STRUCT_SDL_H
# include "fcntl.h"
# include "unistd.h"
# include "stdlib.h"
# include "SDL2/SDL.h"

typedef struct  s_sdl
{
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Texture *text;
    void *pixels;
}               t_sdl;
#endif