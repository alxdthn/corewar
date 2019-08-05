/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 18:45:18 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/04 18:47:23 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_map(char *map)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	line_size;
	unsigned int	bar;

	line_size = MEM_SIZE / 64;
	i = 0;
	j = line_size;
	bar = 4;
	while (i < MEM_SIZE / bar)
	{
		ft_printf("%.2x", map[i++]);
		if (--j)
			ft_putchar(' ');
		else
			ft_putchar('\n');
		if (!j)
			j = line_size;
	}
}

void	print_input(t_list *tmp)
{
	while (tmp)
	{
		ft_printf("%s", STR(tmp));
		tmp = tmp->next;
	}
}
