/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_print_operation_info.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:55:23 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/08 17:21:49 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_header(void)
{
	ft_printf("%{yel}s", "OPERATION INFO:\n");
	ft_printf("__name__|________args_________|"\
	"_carry_|_size_|_dsize_|__description_\n");
}

static int	print_argbyte(char *position, t_op *op, int *byte_ofset)
{
	unsigned char	arg_byte;
	int				i;
	int				print_ofset;
	int				arg_ofset;

	print_ofset = 0;
	arg_byte = position[1];
	i = 0;
	while (i < op->arg_count)
	{
		arg_ofset = get_arg_ofset(get_arg_type(arg_byte), op);
		if (get_arg_type(arg_byte) == T_DIR)
		{
			if (arg_ofset == 4)
				print_ofset += ft_printf("%%%d ",
				ft_reverse_bytes(*(int *)(position + *byte_ofset), sizeof(int)));
			else
				print_ofset += ft_printf("%%%hd ",
				ft_reverse_bytes(*(short *)(position + *byte_ofset), sizeof(short)));
		}
		else
		{
			if (arg_ofset == 2)
				print_ofset += ft_printf("%hd ",
				ft_reverse_bytes(*(short *)(position + *byte_ofset), sizeof(short)));
			else
				print_ofset += ft_printf("r%hhd ", *(position + *byte_ofset));
		}
		(*byte_ofset) += arg_ofset;
		arg_byte <<= 2;
		i++;
	}
	return (print_ofset);
}

static int	print_args(char *position, t_op *op)
{
	int		print_ofset;
	int		byte_ofset;
	int		arg_ofset;

	print_ofset = 0;
	byte_ofset = 1 + ((op->arg_count == 1) ? 0 : 1);
	if (op->arg_count == 1 && op->op_code != 16)
	{
		arg_ofset = get_arg_ofset(op->args[0], op);
		if (arg_ofset == 4)
			print_ofset += ft_printf("%%%d ",
			ft_reverse_bytes(*(int *)(position + byte_ofset), sizeof(int)));
		else if (arg_ofset == 2)
			print_ofset += ft_printf("%%%hd ",
			ft_reverse_bytes(*(short *)(position + byte_ofset), sizeof(short)));
		else
			print_ofset += ft_printf("%%%hhd ", position + byte_ofset);
		byte_ofset += arg_ofset;
	}
	else
		print_ofset = print_argbyte(position, op, &byte_ofset);
	print_ofset = 21 - print_ofset;
	while (--print_ofset >= 0)
		ft_putchar(' ');
	return (byte_ofset);
}

void		print_operation_info(char *position)
{
	t_op	*op;
	int		size;

	print_header();
	op = &op_tab[position[0] - 1];
	ft_printf("%{gre}-8s|", op->op_name);
	size = print_args(position, op);
	if (op->carry)
		ft_printf("|  yes  ");
	else
		ft_printf("|  no   ");
	ft_printf("|%-6d", size);
	ft_printf("|%-7d", op->t_dir_size);
	ft_printf("|%s\n", op->description);
	print_memory(position, size);
}
