/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojerroud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:45:24 by ojerroud          #+#    #+#             */
/*   Updated: 2018/03/22 16:45:25 by ojerroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	error_malloc(void)
{
	write(1, "error malloc\n", 13);
	exit(1);
}

void	error_arg(void)
{
	write(1, "error argv\n", 12);
	write(1, "<filename> <map>\n", 18);
	exit(1);
}

void	error_map(void)
{
	write(1, "error map\n", 10);
	exit(1);
}
