/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/04 17:16:29 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_map(char *map)
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

static void	read_input(t_list *input, int ac, char **av)
{
	int		fd;

	fd = open(av[1], )
}

int		main(int ac, char **av)
{
	t_core	core;

	ft_bzero(&core, sizeof(t_core));
	read_input(&core, ac, av);
	print_map(core.map);
	ft_printf("COREWAAAR!!!\n");
	return (0);
}
