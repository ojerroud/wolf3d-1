/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojerroud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:45:32 by ojerroud          #+#    #+#             */
/*   Updated: 2018/03/22 16:45:34 by ojerroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		init_player(t_env *e)
{
	e->player.pos.x = 0;
	e->player.pos.y = 0;
	e->player.dir.x = -1;
	e->player.dir.y = 0;
	e->player.z = 0;
	e->player.plane.x = 0;
	e->player.plane.y = 0.66;
	e->player.speed_turn = 0.05;
	e->player.speed_move = 0.1;
	e->player.move_up = 0;
	e->player.move_down = 0;
	e->player.move_right = 0;
	e->player.move_left = 0;
}

static void		init_mlx(t_env *e)
{
	e->mlx.mlx = mlx_init();
	e->mlx.bpp = 0;
	e->mlx.s_line = 0;
	e->mlx.img = mlx_new_image(e->mlx.mlx, WIDTH, HEIGHT);
	e->mlx.pxl = mlx_get_data_addr(e->mlx.img, &(e->mlx.bpp), &(e->mlx.s_line),
			&(e->mlx.ed));
}

t_env			init_env(void)
{
	t_env	e;

	e.width = WIDTH;
	e.height = HEIGHT;
	init_player(&e);
	init_mlx(&e);
	e.color_wall = 0x87591A;
	e.color_sky = 0x00cdff;
	e.color_ground = 0x16B84E;
	// e.test = "texture/ceil1.xpm";
	// e.test = mlx_xpm_file_to_image(e.mlx.mlx, "texture/wall1h.xpm", &e.width2, &e.height2);
	texture(&e.text1, TEXTURE_WEST);
	texture(&e.text2, TEXTURE_EAST);
	texture(&e.text3, TEXTURE_NORTH);
	texture(&e.text4, TEXTURE_SOUTH);
	return (e);
}
