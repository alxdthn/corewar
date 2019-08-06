/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_asm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 21:40:21 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/06 23:19:07 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define MAGIC 0x00ea83f3
#define SIZE 2192 //2192 min
#define NAME "dest"
#define COMMENT "i wanna broke your core!"

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

# define CMD_SIZE 7

void	set_arg_value(int a1, int a2, int a3, t_op *op, char *res)
{
	t_arg_type	argbyte;
	int			ofset;
	char		mask;

	argbyte = res[1];
	ofset = 1 + op->arg_type;
	if (argbyte)
	{
		ofset += get_arg_ofset(get_arg_type(argbyte), op);
		res[ofset - 1] = a1;
		argbyte <<= 2;
	}
	if (argbyte)
	{
		ofset += get_arg_ofset(get_arg_type(argbyte), op);
		res[ofset - 1] = a2;
		argbyte <<= 2;
	}
	if (argbyte)
	{
		ofset += get_arg_ofset(get_arg_type(argbyte), op);
		res[ofset - 1] = a3;
		argbyte <<= 2;
	}
}

char	*set_cmd(char *head, int fd)
{
	t_arg_byte	argbyte;
	t_op		*op;
	int			size;
	char		*res;

	op = get_cmd("add");

	argbyte.arg.a1 = (unsigned char)DIR_CODE;
	argbyte.arg.a2 = (unsigned char)IND_CODE;
	argbyte.arg.a3 = (unsigned char)REG_CODE;
	argbyte.arg.a4 = (unsigned char)DIR_CODE;

	size = get_arg_size(op, argbyte.byte);
	ft_printf("%d\n", size);
	res = (char *)ft_memalloc(size);
	res[1] = argbyte.byte;
	set_arg_value(21, 1, -3, op, res);
	res[0] = op->op_code;
	print_operation_info((unsigned char *)res);
	head[139] = size;
	ft_printf("%d\n", size);
	return (res);
}

int		main(void)
{
	int		fd;
	char	head[SIZE];
	char	*cmd;

	system("rm -f destr.cor; touch destr.cor");
	fd = open("destr.cor", O_RDWR);
	ft_bzero(&head, SIZE);
	set_magic(head);
	set_name(head);
	set_comment(head);
	cmd = set_cmd(head, fd);
	write(fd, head, SIZE);
	write(fd, cmd, head[139]);
	close(fd);
}
