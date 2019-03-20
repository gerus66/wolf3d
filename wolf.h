/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 22:02:59 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/20 22:49:45 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "SDL/includes/SDL.h"

typedef struct	s_point
{
	int	x;
	int	y;
	int	h;
}				t_point;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*render;
	SDL_Texture		*text;
	t_vector		*map;
}				t_sdl;

# define USAGE "./wolf [path_to_file_with_map]\n"

# define MAP_DEFAULT "default.map"
//# define H_MAP(x) (x->len / sizeof(t_point) / x->offset)


# define NAME "Wolf3D"
# define WIN_POS_X 100
# define WIN_POS_Y 100
# define WIN_W 1000
# define WIN_H 1000
# define WIN_FLAGS 0

# define REN_FLAGS 0

# define TXT_FORMAT SDL_PIXELFORMAT_ARGB8888
# define TXT_ACCESS SDL_TEXTUREACCESS_STREAMING

/*
** utils
*/

int     clean_all(t_sdl *sdl, char *msg);

/*
** read map from file
*/

void            read_map(t_sdl *sbox, int fd);

/*
** working with map
*/

void    work_map(t_sdl *sbox, unsigned int *map, int len_of_raw);

#endif
