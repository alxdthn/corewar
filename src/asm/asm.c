/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:10:58 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/04 17:30:59 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		printer(int ac, char **av)
{
	if (ac == 2)
		print_memory(av[1]);
	else
		ft_putstr("no arg!\n");
	return (0);
}

// void	translator(char **f, )

int		main(int ac, char **av)
{
	char	*file;
	char	**per_str;
	int		fd;

	if (ac == 1)
		return (0);
	if ((fd = open(av[ac - 1],O_RDONLY)) < 3)
		return (0);
	ft_read_to_str(fd, &file, 1000);
//	tranlator(per_str = ft_strsplit(file, '\n'));
	// fd = 0;
	// while (per_str[fd])
	// 	ft_printf("%s\n", per_str[fd++]);
	return (0);
}
