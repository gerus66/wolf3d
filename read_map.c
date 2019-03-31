/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 22:02:06 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/31 21:27:39 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** starting value for size of vector, just for speed of reading from map
*/

#define V_SIZE 100

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
	free(line);
	len = len ? len : ft_arlen(ar);
	if (ft_arlen(ar) != len)
		exit(clean_all(sbox, "Invalid map\n"));
	j = -1;
	while (++j < len)
	{
		if (!(pt = (t_point *)malloc(sizeof(t_point))))
			exit(clean_all(sbox, "Cant allocate memory"));
		*pt = (t_point){j, i, ft_atoi(ar[j])};
		free(ar[j]);
		if (!(ft_vadd(sbox->map, pt, sizeof(t_point))))
			exit(clean_all(sbox, "Cant allocate memory"));
		free(pt);
	}
	free(ar);
	return (j);
}

/*
** read map from file [fd]
** initialize field [sbox.map] of [sbox] structure
** if smth goes wrong, clean all and display message
** validate map - same length of all lines, more then 1 point
*/

void			read_map(t_sdl *sbox, int fd)
{
	char		*line;
	size_t		i;
	size_t		len;
	int			r;

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
}
