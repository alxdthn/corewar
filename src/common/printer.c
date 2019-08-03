/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:08:26 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/03 21:22:19 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printer(char *av)
{
	int 	i;
	char	*str;
	int		fd;
	size_t	ret;

	i = 0;
	fd = open(av, O_RDONLY);
	ret = get_next_line(fd, &str);
	while (i < ret)
	{
		ft_printf("%.2hhx", str[i++]);
		ft_printf("%.2hhx ", str[i]);
		i++;
	}
	ft_putchar('\n');
}
