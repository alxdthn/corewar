/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_operation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:39:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 13:51:11 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		validate_operation(t_core *core, t_list *carriage)
{
	int		i;
	int		byte_ofset;
	char	argbyte;
	char	arg_type;

	byte_ofset = 1 + ARG_TYPE;
	argbyte = (ARG_TYPE) ? BYTE(ARG_BYTE) : (get_arg_code(OPER_ARGS[0]) << 6);
	i = 0;
	while (i < CRG->op_info->arg_count)
	{
		arg_type = get_arg_type(argbyte);
		if ((arg_type & OPER_ARGS[i]) != arg_type)
			return (get_function_size(argbyte, CRG->op_info));
		if (arg_type == T_REG && (BYTE(CURRENT + byte_ofset) < 0
		|| BYTE(CURRENT + byte_ofset) > REG_NUMBER))
			return (get_function_size(argbyte, CRG->op_info));
		i++;
		argbyte <<= 2;
		byte_ofset += get_arg_ofset(arg_type, CRG->op_info);
 	}
	return (0);
}
