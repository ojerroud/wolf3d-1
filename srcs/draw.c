#include "wolf.h"

void			put_pxl(t_env *e, int x, int y, unsigned int c)
{
	int		i;

	i = (x * 4) + (y * e->mlx.s_line);
	e->mlx.pxl[i] = c;
	e->mlx.pxl[++i] = c + 10;
	e->mlx.pxl[++i] = c + 20;
}

// void 			add_texture(t_env *e, char *name_texture)
// {
// 	mlx_xpm_to_image();
// }

void			draw_line(t_env *e, int x, int start, int end)
{
	int				i;

	i = -1;
	while (++i < start + e->player.z)
		put_pxl(e, x, i, e->color_sky);
	i--;
	while (++i <= end + e->player.z && i < e->height)
		put_pxl(e, x, i, e->color_wall);
	i--;
	while (++i < e->height)
		put_pxl(e, x, i, e->color_ground);
}
