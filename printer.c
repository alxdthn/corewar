/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:08:26 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/03 18:32:07 by skrystin         ###   ########.fr       */
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
		j = 0;
		while (j < 16)
			ft_printf("%.4x ", str[i] << (j += 4) & 0xFF000000);
		i++;
	}
	return (0);
}
