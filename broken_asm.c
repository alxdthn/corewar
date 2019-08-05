/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_asm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 21:40:21 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/05 17:04:03 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#define MAGIC 0x00ea83f3
#define SIZE 2197 //2192 min
#define NAME "destr"
#define COMMENT "i wanna broke your core!"
#define BAD_CMD "live %42"

void	set_magic(char *buf)
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

void	set_name(char *buf)
{
	int		i;

	i = 0;
	while (NAME[i])
	{
		(buf + 4)[i] = NAME[i];
		i++;
	}
}

void	set_cmd(char *buf)
{
	int		i;
	long	cmd;

	i = 0;
	cmd = BAD_CMD;
	buf[139] = 5;
	while (cmd)
	{
		(buf + 2192)[i] = cmd;
		cmd >>= 8;
	}
}

void	set_comment(char *buf)
{
	int		i;

	i = 0;
	while (COMMENT[i])
	{
		(buf + 140)[i] = COMMENT[i];
		i++;
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
	set_magic(buf);
	set_name(buf);
	set_comment(buf);
	set_cmd(buf);
	write(fd, buf, SIZE);
	close(fd);
}
