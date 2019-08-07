/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_asm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 21:40:21 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 16:26:21 by nalexand         ###   ########.fr       */
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

static void	set_arg(t_arg_type *argbyte, int *ofset, char *res, int arg, t_op *op)
{

	*ofset = get_arg_ofset(get_arg_type(*argbyte), op);
	if (*ofset == 2)
		((short *)res)[*ofset - 1] = arg;
	else if (*ofset == 4)
		((int *)res)[*ofset - 1] = arg;
	else
		res[*ofset - 1] = arg;
	(*argbyte) <<= 2;
}

void		set_arg_value(int a1, int a2, int a3, t_op *op, char *res)
{
	t_arg_type	argbyte;
	int			byte_ofset;
	int			ofset;
	char		mask;

	argbyte = res[1];
	ofset = 1 + op->arg_type;
	if (op->arg_count == 1)
	{
		res[1] = 0;
		byte_ofset = 1;
		ofset = get_arg_ofset(op->args[0], op);
		if (ofset == 4)
		{
			a1 = ft_reverse_bytes((long )a1, sizeof(int));
			ft_memcpy(res + byte_ofset, &a1, sizeof(int));
		}
		else if (ofset == 2)
		{
			a1 = ft_reverse_bytes((long )a1, sizeof(short));
			ft_memcpy(res + byte_ofset, &a1, sizeof(int));
		}
		else
			res[byte_ofset] = a1;
		byte_ofset += ofset;
	}
	else
	{
		byte_ofset = 2;
		if (argbyte)
			set_arg(&argbyte, &ofset, res, a1, op);
		if (argbyte)
			set_arg(&argbyte, &ofset, res, a2, op);
		if (argbyte)
			set_arg(&argbyte, &ofset, res, a3, op);

	}
}

char	*set_cmd(char *head, int fd)
{
	t_arg_byte	argbyte;
	t_op		*op;
	int			size;
	char		*res;

	op = get_cmd("live");

	argbyte.arg.a1 = (char)DIR_CODE;
	argbyte.arg.a2 = (char)0;
	argbyte.arg.a3 = (char)0;
	argbyte.arg.a4 = (char)0;

	size = get_arg_size(op, argbyte.byte);
	ft_printf("%d\n", size);
	res = (char *)ft_memalloc(size);
	res[1] = argbyte.byte;
	set_arg_value(2000000000, 0, 0, op, res);
	res[0] = op->op_code;
	print_operation_info(res);
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
