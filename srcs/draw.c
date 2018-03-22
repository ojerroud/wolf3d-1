/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojerroud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:45:16 by ojerroud          #+#    #+#             */
/*   Updated: 2018/03/22 16:45:17 by ojerroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

void			put_pxl(t_env *e, int x, int y, unsigned int c)
{
	int		i;

	i = (x * 4) + (y * e->mlx.s_line);
	e->mlx.pxl[i] = c;
	e->mlx.pxl[++i] = c >> 8;
	e->mlx.pxl[++i] = c >> 16;
}

unsigned int	wall_orientation(t_env *e, int x, int y)
{
	if (e->ray.hit_side == 1)
	{
		if ((e->ray.step.x == -1 && e->ray.step.y == -1) ||
			(e->ray.step.x == 1 && e->ray.step.y == -1))
			return (e->text1.texture[x % e->text1.max.y][y % e->text1.max.x]);
		if ((e->ray.step.x == -1 && e->ray.step.y == 1) ||
			(e->ray.step.x == 1 && e->ray.step.y == 1))
			return (e->text2.texture[x % e->text2.max.y][y % e->text2.max.x]);
	}
	if ((e->ray.step.x == -1 && e->ray.step.y == -1) ||
		(e->ray.step.x == -1 && e->ray.step.y == 1))
		return (e->text3.texture[x % e->text3.max.y][y % e->text3.max.x]);
	return (e->text4.texture[x % e->text4.max.y][y % e->text4.max.x]);
}

void			draw_line(t_env *e, int x, int start, int end)
{
	int				i;
	int				tmpy;
	int				tmp;

	i = -1;
	while (++i < start + e->player.z)
		put_pxl(e, x, i, e->color_sky);
	i--;
	tmp = i;
	tmpy = 0;
	while (++i < e->height / 2)
		put_pxl(e, x, i, wall_orientation(e, ++tmpy, x));
	i = end - 1;
	tmpy = 0;
	while (--i >= e->height / 2)
		put_pxl(e, x, i, wall_orientation(e, ++tmpy, x));
	i = end - 1;
	while (++i < e->height)
		put_pxl(e, x, i, e->color_ground);
}
