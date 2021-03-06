/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojerroud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:47:10 by ojerroud          #+#    #+#             */
/*   Updated: 2018/03/22 16:47:11 by ojerroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		read_pos(int fd, t_env *e)
{
	char	*line;
	char	**line_split;
	int		i;

	i = -1;
	if (get_next_line(fd, &line) < 1)
		error_map();
	line_split = ft_strsplit(line, ' ');
	ft_strdel(&line);
	while (line_split[++i] != '\0')
		;
	if (i != 4)
		error_map();
	e->map_width = ft_atoi(line_split[0]);
	e->map_height = ft_atoi(line_split[1]);
	e->player.pos.x = ft_atoi(line_split[2]) - 0.5;
	e->player.pos.y = ft_atoi(line_split[3]) - 0.5;
	if (e->map_width < 0 || e->map_height < 0 || e->player.pos.x < 0 ||
			e->player.pos.y < 0 || e->player.pos.x >= e->map_width ||
			e->player.pos.y >= e->map_width)
		error_map();
	i = -1;
	while (line_split[++i] != '\0')
		ft_strdel(&line_split[i]);
	free(line_split);
}

static void		read_line(char *line, int y, int **map, t_env *e)
{
	int		x;
	char	**line_split;

	x = -1;
	if (y >= e->map_height)
		error_map();
	line_split = ft_strsplit(line, ' ');
	ft_strdel(&line);
	map[y] = (int *)malloc(sizeof(int) * e->width);
	while (line_split[++x] != '\0')
	{
		if (!(line_split[x][0] >= '0' && line_split[x][0] <= '9'
					&& ft_atoi(line_split[x]) >= 0 && x < e->map_width))
			error_map();
		map[y][x] = ft_atoi(line_split[x]);
		ft_strdel(&line_split[x]);
		if ((x == 0 || x == e->map_width - 1 || y == 0 || y == e->map_height -
					1) && map[y][x] == 0)
			error_map();
	}
	free(line_split);
	if (x != e->map_width)
		error_map();
}

static int		read_file(int fd, t_env *e)
{
	char	*line;
	int		y;

	y = -1;
	read_pos(fd, e);
	e->map = (int **)malloc(sizeof(int *) * e->map_height);
	while (get_next_line(fd, &line) == 1)
		read_line(line, ++y, e->map, e);
	if (e->map[(int)e->player.pos.x][(int)e->player.pos.y] != 0)
		error_map();
	return (1);
}

int				open_file(t_env *e, char *f)
{
	int		fd;

	fd = open(f, O_RDONLY);
	if (fd < 0)
		return (0);
	return (read_file(fd, e));
}
