/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_print_operation_info.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:55:23 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 14:54:57 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_header(void)
{
	ft_printf("%{yel}s", "OPERATION INFO:\n");
	ft_printf("__name__|________args_________|_carry_|_size_|_dsize_|__description_\n");
}

static int	print_args(const unsigned char *position, t_op *op)
{
	int				ofset;
	unsigned char	arg_byte;
	int				byte_ofset;
	int				i;

	ofset = 0;
	byte_ofset = 1 + op->arg_type;
	if (op->arg_count == 1)
	{
		if (op->args[0] == T_DIR)
			ofset += ft_printf("%%%d ", position[byte_ofset += get_arg_ofset(T_DIR, op)]);
		else if (op->args[0] == T_REG)
			ofset += ft_printf("r%d ", position[byte_ofset += get_arg_ofset(T_REG, op)]);
	}
	else
	{
		arg_byte = position[1];
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
	return (byte_ofset);
}

void		print_operation_info(const unsigned char *position)
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
	print_memory((char *)position, size);
}
