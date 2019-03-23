/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 22:02:59 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/23 20:05:07 by mbartole         ###   ########.fr       */
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

typedef struct 	s_view
{
	int	x;
	int	y;
	float	angle;
}				t_view;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*render;
	SDL_Texture		*text;
	SDL_Texture		*plane;
	SDL_Texture		*mapa;
	unsigned char	flags[1];
	t_vector		*map;
	t_view			cam;
}				t_sdl;

# define USAGE "./wolf [path_to_file_with_map]\n"

# define MAP_DEFAULT "default.map"
//# define H_MAP(x) (x->len / sizeof(t_point) / x->offset)


# define NAME "Wolf3D"
# define WIN_POS_X 1000
# define WIN_POS_Y 1000
# define WIN_W 700
# define WIN_H 700
# define WIN_FLAGS 0

# define REN_FLAGS 0

# define TXT_FORMAT SDL_PIXELFORMAT_ARGB8888
# define TXT_ACCESS SDL_TEXTUREACCESS_STREAMING

# define FOV M_PI / 3
# define CAM_H 32
# define WALL_H 64
# define STEP (float)FOV / WIN_W
# define DIST (int)(WIN_W / 2 / tan(FOV / 2))
# define BLOCK 64

# define ABS(x) ((x) > 0 ? (x) : -(x))

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
void    work_it(t_sdl *sbox, unsigned int *map, int len_of_raw);

#endif
