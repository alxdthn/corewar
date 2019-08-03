/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:08:26 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/03 18:58:07 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		main(int ac, char **av)
{
	int 	i;
	char	*str;
	int		fd;
	size_t	ret;
	int		j;

	i = 0;
	str = 0;
	fd = open(av[1], O_RDONLY);
	ret = get_next_line(fd, &str);
	while (i < ret)
	{
		ft_printf("%.2hhx", str[i++]);
		ft_printf("%.2hhx ", str[i]);
		i++;
	}
	ft_printf("\n");
	return (0);
}
