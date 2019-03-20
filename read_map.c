/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 22:02:06 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/20 22:40:30 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** starting value for size of vector, just for speed of reading from map
*/
#define V_SIZE 100

/*
** relation size of image to size of map at start
*/
/*#define START_SCALE 1.5*/

/*
** default color for start
*/
/*#define COLOR_DEFAULT 0x00EEFECE
#define COLOR_BOTTOM 0x00FFC400
#define COLOR_GROUND 0x0000FF1A
#define COLOR_TOP 0x000994D0*/

/*#define BASE16 "0123456789ABCDEF"*/

/*
** clean all if smth going wrong during reading map
** display message [mes]
*/
/*
int				clean(t_vector *map, char *mes)
{
	if (map)
		ft_vdel(&map);
	ft_putendl(mes);
	exit(0);
}
*/
/*
** set color of point from file or by default
*/
/*
static void		set_point_color(void *mlx, t_point *pt, char *cl)
{
	char	**ar;
	int		color;

	ar = ft_strsplit(cl, ',');
	if (ar[1])
		ar[1] = ar[1] + 2;
	color = ar[1] ? ft_atoibase(ar[1], BASE16) : COLOR_DEFAULT;
	pt->color.cl = mlx_get_color_value(mlx, color);
}
*/
/*
void			set_map_color(t_imgbox *ibox)
{
	int		i;
	int		map_size;
	t_point	*cp;

	i = -1;
	map_size = ibox->map->len / sizeof(t_point);
	cp = (t_point *)ibox->map->cont;
	while (++i < map_size)
	{
		if (cp->z < 0)
			cp->color.cl = mlx_get_color_value(ibox->mlx, COLOR_BOTTOM);
		else if (cp->z > 0)
			cp->color.cl = mlx_get_color_value(ibox->mlx, COLOR_TOP);
		else
			cp->color.cl = mlx_get_color_value(ibox->mlx, COLOR_GROUND);
		cp++;
	}
}
*/
/*
** handle one line of map
** return length of line (number of  points)
*/

static size_t	one_line(size_t len, char *line, t_sdl *sbox, size_t i)
{
	char		**ar;
	size_t		j;
	t_point		*pt;

	ar = ft_strsplit(line, ' ');
	len = len ? len : ft_arlen(ar);
	if (ft_arlen(ar) != len)
		exit(clean_all(sbox, "Invalid map\n"));
	j = -1;
	while (++j < len)
	{
		if (!(pt = (t_point *)malloc(sizeof(t_point))))
			exit(clean_all(sbox, "Cant allocate memory"));
		*pt = (t_point){j, i, ft_atoi(ar[j])};
//		set_point_color(ibox->mlx, pt, ar[j]);
		if (!(ft_vadd(sbox->map, pt, sizeof(t_point))))
			exit(clean_all(sbox, "Cant allocate memory"));
		free(pt);
	}
	return (j);
}

/*
** read map from file [fd]
** initialize field [sbox.map] of [sbox] structure
** if smth goes wrong, clean all and display message
** validate map - same length of all lines, more then 1 point
*/
/*
** OLD
** move map to 0 of all corrdinates (then refresh [ibox.mov] matrix)
** initialize [ibox.scl] scale matrix so map fit the window
*/

void			read_map(t_sdl *sbox, int fd)
{
	char		*line;
	size_t		i;
	size_t		len;
	int			r;
//	size_t		h_map;

	if (!(ft_vnew(&(sbox->map), sizeof(t_point) * V_SIZE)))
		exit(0);
	len = 0;
	i = 0;
	while ((r = get_next_line(fd, &line)))
	{
		if (r == -1)
			exit(clean_all(sbox, "Invalid file\n"));
		len = one_line(len, line, sbox, i++);
	}
	if (!(sbox->map->offset = len) || len == 1)
		exit(clean_all(sbox, "Invalid map\n"));
//	h_map = H_MAP(sbox->map);
//	move(ibox->mov, -(int)W_MAP(ibox->map) / 2, -(int)h_map / 2);
//	map_loop(ibox->map, ibox->mov);
//	init_matrix(ibox->mov);
//	scale_h(ibox->scl, (double)IMG_SIZE / START_SCALE / (double)
//			(W_MAP(ibox->map) > h_map ? W_MAP(ibox->map) : h_map));
}

