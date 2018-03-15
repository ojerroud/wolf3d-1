#include "wolf.h"

void			put_pxl(t_env *e, int x, int y, unsigned int c)
{
	int		i;

	i = (x * 4) + (y * e->mlx.s_line);
	e->mlx.pxl[i] = c;
	e->mlx.pxl[++i] = c >> 8;
	e->mlx.pxl[++i] = c >> 16;
}

// int 			*load_texture(t_env *e)
// {
// 	int 	tmp[9] = {0x2D4020, 0x344B25, 0x405D2D, 0x2D4020, 0x344B25, 0x405D2D, 0x2D4020, 0x344B25, 0x405D2D};
// 	return (tmp);
// }

void			draw_line(t_env *e, int x, int start, int end)
{
	int				i;

	i = -1;
	while (++i < start + e->player.z)
		put_pxl(e, x, i, e->color_sky);
	i--;
	e->i = -1;
	while (++i <= end + e->player.z && i < e->height)
	{
		e->color_wall = 0x65536 * 254 * (x != i && x != end - i);
		put_pxl(e, x, i, e->color_wall);
	}
	i--;
	while (++i < e->height)
		put_pxl(e, x, i, e->color_ground);
}
