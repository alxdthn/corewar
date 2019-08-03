/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:08:26 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/03 18:24:54 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		main(int ac, char **av)
{
	int 	i;
	char	*str;
	int		fd;
	size_t	ret;

	i = 0;
	str = 0;
	fd = open(av[1], O_RDONLY);
	ret = get_next_line(fd, &str);
	while (i < ret)
	{
		ft_printf("%#.5b", str[i++]);
	}
	return (0);
}
