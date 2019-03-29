/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 22:02:59 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/29 21:40:33 by mbartole         ###   ########.fr       */
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
	int	horiz;
	float	angle;
}				t_view;

/*
** flags: 0 - show mini-map; 
**		  1 - swith on texture on walls
*/

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*render;
	SDL_Texture		*text;
	SDL_Texture		*plane;
	SDL_Texture		*mapa;
	unsigned char	flags[2];
	int				mouse_pos[2];
	t_vector		*map;
	t_view			cam;
	SDL_Texture		**texture_pack;
}				t_sdl;

# define UP 26
# define RIGHT 7
# define DOWN 22
# define LEFT 4

# define USAGE "./wolf [path_to_file_with_map]\n"

# define MAP_DEFAULT "default.map"
# define MAP(x) ((t_point *)((x)->cont))
# define MAP_W(x) ((int)x->offset)
# define MAP_H(x) ((int)(x->len / x->offset / sizeof(t_point)))


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

# define QT_12(x) ((x) >= 0)
# define QT_34(x) ((x) <= 0)
# define QT_14(x) ((x) <= M_PI / 2 && (x) >= -M_PI / 2)
# define QT_23(x) ((x) >= M_PI / 2 || (x) <= -M_PI / 2)

# define ROT_STEP M_PI / 128
# define MOV_STEP BLOCK / 16

/*
** utils
*/

int     		clean_all(t_sdl *sdl, char *msg);
void			reprint_all(t_sdl *sdl);

/*
** read map from file
*/

void            read_map(t_sdl *sbox, int fd);

/*
** create mini-map
*/

void    draw_map(t_sdl *sdl, unsigned int *map);

/*
** casting of walls
*/

void    pixels_to_render(t_sdl *sbox, unsigned int *map);
void    texts_to_render(t_sdl *sbox);

/*
** painting of walls
*/

SDL_Texture             **load_textures(t_sdl *sdl);
void					paint_walls(t_sdl *sdl, float ang, int *params, char side);

#endif
