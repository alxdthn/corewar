/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_asm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 21:40:21 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/06 22:05:51 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define MAGIC 0x00ea83f3
#define SIZE 2192 //2192 min
#define NAME "dest"
#define COMMENT "i wanna broke your core!"

t_op    		op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 4, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 4, 1},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 4, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 4, 1},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 1},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 4, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 4, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 4, 1},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 2, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 2, 0},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 2, 0},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 2, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 4, 1},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 2, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 2, 0},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 4, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0}
};

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

void	memory(char *mem, ssize_t size)
{
	int 	i;
	int		j;

	i = 0;
	j = 8;
	while (i < size)
	{
		ft_printf("%.2hhx", mem[i++]);
		if (i < size)
			ft_printf("%.2hhx", mem[i]);
		if (--j)
			ft_putchar(' ');
		else
		{
			ft_putchar('\n');
			j = 8;
		}
		i++;
	}
	ft_putchar('\n');
}

int	print_operation(char *position)
{
	t_op			*op;
	int				i;
	unsigned char	arg_byte;
	int				ofset;
	int				byte_ofset;

	ft_printf("OPERATION INFO:\n");
	op = &op_tab[position[0] - 1];
	ft_printf("__name__|________args_________|_carry_|_size_|_dsize_|__description_\n");
	ft_printf("%-8s|", op->op_name);
	ofset = 0;
	if (op->arg_count == 1 && op->args[0] == T_DIR)
		ofset += ft_printf("%d ", position[4]);
	else
	{
		arg_byte = position[1];
		byte_ofset = 1 + op->arg_type;
		i = 0;
		while (i < op->arg_count)
		{
			if ((arg_byte & 0xC0) == (REG_CODE << 6))
				ofset += ft_printf("r%d, ", position[(byte_ofset += T_REG) - 1]);
			else if ((arg_byte & 0xC0) == (DIR_CODE << 6))
				ofset += ft_printf("%%%d, ", position[(byte_ofset += op->t_dir_size) - 1]);
			else if ((arg_byte & 0xC0) == (IND_CODE << 6))
				ofset += ft_printf("%d, ", position[(byte_ofset += IND_SIZE) - 1]);
			arg_byte <<= 2;
			i++;
		}
	}
	ofset = 21 - ofset;
	while (--ofset >= 0)
		ft_putchar(' ');
	if (op->carry)
		ft_printf("|  yes  ");
	else
		ft_printf("|  no   ");
	ft_printf("|%-6d", byte_ofset);
	ft_printf("|%-7d", op->t_dir_size);
	ft_printf("|%s\n", op->description);
	return (byte_ofset);
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

	op = get_cmd("xor");

	argbyte.arg.a1 = (unsigned char)DIR_CODE;
	argbyte.arg.a2 = (unsigned char)REG_CODE;
	argbyte.arg.a3 = (unsigned char)REG_CODE;
	argbyte.arg.a4 = (unsigned char)0;

	size = get_arg_size(op, argbyte.byte);
	ft_printf("%d\n", size);
	res = (char *)ft_memalloc(size);
	res[1] = argbyte.byte;
	set_arg_value(21, 1, 3, op, res);
	res[0] = op->op_code;
	print_operation(res);
	memory(res, size);
	head[139] = size;
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
