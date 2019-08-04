/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:08:26 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/04 14:10:24 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_memory(char *av)
{
	int 	i;
	char	*str;
	int		fd;
	size_t	ret;

	i = 0;
	fd = open(av, O_RDONLY);
	ret = get_next_line(fd, &str);
	while (i < ret - 1)
	{
		ft_printf("%.2hhx", str[i++]);
		ft_printf("%.2hhx ", str[i]);
		i++;
	}
	ft_putchar('\n');
}
