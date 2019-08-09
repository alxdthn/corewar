/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 02:49:21 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 03:08:59 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_arg_value_debug(t_list *carriage, char *op, char arg_byte, char *map)
{
	int		arg;

	if (get_arg_type(arg_byte) == T_REG)
	{
		ft_printf("T_REG -> get arg %.2x (r%hhd)\n", CRG->reg[*(op + 2) - 1], CRG->reg[*(op + 2) - 1]);
		return (CRG->reg[*(op + 2) - 1]);
	}
	else if (get_arg_type(arg_byte) == T_DIR)
	{
		ft_printf("T_DIR(%d) -> get arg %.4x -> rev %.4x (%%%d)\n",
		CRG->op_info->t_dir_size, *((int *)(op + 2)),
		ft_reverse_bytes(*((int *)(op + 2)), sizeof(int)),
		ft_reverse_bytes(*((int *)(op + 2)), sizeof(int)));
		if (CRG->op_info->t_dir_size == 4)
			return (ft_reverse_bytes(*((int *)(op + 2)), sizeof(int)));
		else
			return (ft_reverse_bytes(*((short *)(op + 2)), sizeof(short)));
	}
	else
	{
		ft_printf("T_IND -> get arg: ");
		arg = *((short *)(op + 2));
		ft_printf("%#.2x -> ", arg);
		ft_printf("rev arg: ");
		arg = ft_reverse_bytes(arg, sizeof(short));
		ft_printf("%#.2x (%d) -> ", arg, arg);
		ft_printf("get adr: ");
		ft_printf("pos %d + arg %d %% idx %d -> " , CRG->position, arg, IDX_MOD);
		arg = CRG->position + arg % IDX_MOD;
		ft_printf("%d -> ", arg);
		ft_printf("get value: ");
		arg = *(short *)(map + arg);
		ft_printf("%d -> ", arg);
		ft_printf("rev value: ");
		arg = ft_reverse_bytes(arg, sizeof(short));
		ft_printf("%d\n", arg);
		return (arg);		
	}
}

int		get_arg_value(t_list *carriage, char *op, char arg_byte, char *map)
{
	if (get_arg_type(arg_byte) == T_REG)
		return (CRG->reg[*(op + 2) - 1]);
	else if (get_arg_type(arg_byte) == T_DIR)
	{
		if (CRG->op_info->t_dir_size == 4)
			return (ft_reverse_bytes(*((int *)(op + 2)), sizeof(int)));
		else
			return (ft_reverse_bytes(*((short *)(op + 2)), sizeof(short)));
	}
	else
		return (ft_reverse_bytes(*((short *)(map + CRG->position
		+ ft_reverse_bytes(*((short *)(op + 2)),
		sizeof(short)) % IDX_MOD)), sizeof(short)));
}
