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

unsigned int	wall_orientation(t_env *e, int y, int x, double tmp2)
{
	if (e->ray.hit_side == 1)
	{
		if ((e->ray.step.x == -1 && e->ray.step.y == -1) ||
			(e->ray.step.x == 1 && e->ray.step.y == -1))
			return (e->text1.texture[(int)(x / tmp2) % e->text1.max.y][(int)(y / tmp2) % e->text1.max.x]);
		if ((e->ray.step.x == -1 && e->ray.step.y == 1) ||
			(e->ray.step.x == 1 && e->ray.step.y == 1))
			return (e->text2.texture[(int)(x / tmp2) % e->text2.max.y][(int)(y / tmp2) % e->text2.max.x]);
	}
	if ((e->ray.step.x == -1 && e->ray.step.y == -1) ||
		(e->ray.step.x == -1 && e->ray.step.y == 1))
		return (e->text3.texture[(int)(x / tmp2) % e->text3.max.y][(int)(y / tmp2) % e->text3.max.x]);
	return (e->text4.texture[(int)(x / tmp2) % e->text4.max.y][(int)(y / tmp2) % e->text4.max.x]);
}

void			draw_line(t_env *e, int x, int start, int end)
{
	int				i;
	int				tmpy;
	int				tmp;
	double			tmp2;

	i = -1;
	// (!x) ? tmpy = text - 1 : 0;
	// (!x) ? printf("%d\n", tmpy) : 0;
	// (!x) ? text = text / 64 : 0;
	tmpy = 0;
	// text = 0;
	while (++i < start + e->player.z)
		put_pxl(e, x, i, e->color_sky);
	i--;
	tmp = i;
	tmp2 = (end - start) / (double)64;
	// printf("%d\n", text % 64);

	while (++i <= end)
		put_pxl(e, x, i, wall_orientation(e, x, ++tmpy, tmp2));
	i--;
	while (++i < e->height)
		put_pxl(e, x, i, e->color_ground);
}
