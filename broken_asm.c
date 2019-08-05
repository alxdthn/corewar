/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_asm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 21:40:21 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/04 22:34:38 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#define MAGIC 0x00ea83f3
#define SIZE 2197 //2192 min
#define NAME "moes"
#define BAD_CMD 0xFFFFFFFFFF

void	get_magic(char *buf)
{
	int		magic;
	int		i;
	int		ofset;

	magic = MAGIC;
	i = 0;
	ofset = 32;
	while (ofset)
		buf[i++] = magic >> (ofset -= 8);
}

void	get_name(char *buf)
{
	int		i;

	i = 0;
	while (NAME[i])
	{
		buf[i + 4] = NAME[i];
		i++;
	}
}

void	get_cmd(char *buf)
{
	int		i;
	long	cmd;

	i = 2192;
	cmd = BAD_CMD;
	buf[139] = 5;
	while (cmd)
	{
		buf[i++] = cmd;
		cmd >>= 8;
	}
}

int		main(void)
{
	int		fd;
	char	buf[SIZE];

	system("rm -f destr.cor; touch destr.cor");
	fd = open("destr.cor", O_RDWR);
	ft_bzero(&buf, SIZE);
	ft_printf("%zu\n", ft_strlen(NAME));
	get_magic(buf);
	get_name(buf);
	get_cmd(buf);
	write(fd, buf, SIZE);
	close(fd);
}
