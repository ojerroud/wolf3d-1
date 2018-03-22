/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojerroud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:17:08 by ojerroud          #+#    #+#             */
/*   Updated: 2018/03/19 12:17:10 by ojerroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				**get_tab(t_text *text, int *params,
	t_texture_color *t_colors, char **str)
{
	int	compteur;
	int	i;
	int	j;

	text->texture = (int **)malloc(sizeof(int*) * text->max.y);
	i = -1;
	while (++i < text->max.y)
	{
		text->texture[i] = (int *)malloc(sizeof(int) * text->max.x);
		j = -1;
		while (++j < text->max.x)
		{
			compteur = -1;
			while (++compteur < params[2])
				if (t_colors[compteur].id == str[i][j])
				{
					text->texture[i][j] = t_colors[compteur].color;
					break ;
				}
		}
		ft_strdel(&str[i]);
	}
	ft_strdel(str);
	return (text->texture);
}

char			**stock_buffer(t_text *text, char *line, int fd)
{
	int		compteur;
	char	**str;

	compteur = -1;
	if (!(str = (char **)malloc(sizeof(char *) * (text->max.y + 1))))
		return (0);
	str[text->max.y] = NULL;
	while (++compteur < text->max.y)
	{
		if (get_next_line(fd, &line) <= 0)
			return (0);
		if (line[0] != 34)
			compteur--;
		else
		{
			str[compteur] = ft_strnew(text->max.x);
			str[compteur] = ft_strncpy(str[compteur], line + 1, text->max.x);
		}
		ft_strdel(&line);
	}
	return (str);
}

t_texture_color	*get_color(char *line, int fd, int *params)
{
	int				compteur;
	char			*color;
	t_texture_color	*tab;

	tab = (t_texture_color *)malloc(sizeof(t_texture_color) * params[2]);
	compteur = -1;
	while (++compteur < params[2])
	{
		if (get_next_line(fd, &line) <= 0)
			return (0);
		if (line[0] != 34)
			compteur--;
		else
		{
			tab[compteur].id = line[1];
			color = ft_strsub(line, 6, 6);
			tab[compteur].color = (color[0] == 'o') ? 0 : ft_hexa_to_int(color);
			ft_strdel(&color);
		}
		ft_strdel(&line);
	}
	return (tab);
}

int				*param(t_text *text, char *line)
{
	char	**str;
	int		i;
	int		*params;

	params = (int *)malloc(sizeof(int) * T_PARAMS);
	str = ft_strsplit(&line[1], ' ');
	ft_strdel(&line);
	i = -1;
	while (++i < T_PARAMS)
		params[i] = ft_atoi(str[i]);
	i = -1;
	while (str[++i])
		ft_strdel(&str[i]);
	free(str);
	text->max.x = params[1];
	text->max.y = params[0];
	return (params);
}

void			texture(t_text *text, char *xpm)
{
	int				fd;
	char			*line;
	char			**str;
	int				*params;
	t_texture_color	*t_colors;

	if (!(fd = open(xpm, O_RDONLY)))
		exit(0);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 34)
		{
			params = param(text, line);
			t_colors = get_color(line, fd, params);
			str = stock_buffer(text, line, fd);
			text->texture = get_tab(text, params, t_colors, str);
			free(t_colors);
			free(params);
			break ;
		}
		ft_strdel(&line);
	}
	close(fd);
}
