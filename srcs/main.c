/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojerroud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:45:48 by ojerroud          #+#    #+#             */
/*   Updated: 2018/03/22 16:45:49 by ojerroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		read_option(t_env *e, int argc, char **argv)
{
	if (argc != 2)
		error_arg();
	if (open_file(e, argv[1]) == 0)
		error_map();
}

int				main(int argc, char **argv)
{
	t_env	e;

	e = init_env();
	read_option(&e, argc, argv);
	e.mlx.win = mlx_new_window(e.mlx.mlx, WIDTH, HEIGHT, "Wolf3d");
	mlx_do_key_autorepeatoff(e.mlx.mlx);
	mlx_loop_hook(e.mlx.mlx, loop_hook, &e);
	mlx_hook(e.mlx.win, 17, (1L << 1), red_cross, 0);
	mlx_hook(e.mlx.win, KEY_PRESS, KEY_PRESS_MASK, key_press, &e);
	mlx_key_hook(e.mlx.win, key_hook, &e);
	mlx_loop(e.mlx.mlx);
	return (0);
}
