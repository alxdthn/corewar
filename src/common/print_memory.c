/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:08:26 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/04 20:00:24 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_memory(char *mem, ssize_t size)
{
	int 	i;
	int		j;

	i = 0;
	j = 8;
	while (i < size)
	{
		ft_printf("%.2hhx", mem[i++]);
		if (i < size)
			ft_printf("%.2hhx", mem[i]);
		if (--j)
			ft_putchar(' ');
		else
		{
			ft_putchar('\n');
			j = 8;
		}
		i++;
	}
	ft_putchar('\n');
}
