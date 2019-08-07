/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_operation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:39:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 19:03:24 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Валидация операции, возвращает количествой байт
**	на которые должна перейти каретка в случае невалидной операции.
**	(Вывод ошибок временный)
*/

int		validate_operation(t_list *carriage)
{
	t_arg_type	argbyte;
	int			i;
	int			byte_ofset;
	char		arg_type;

	CRG->op_info = NULL;
	if (CRG->op[OPERATION_CODE] < 1 || CRG->op[OPERATION_CODE] > 16)
		return (ft_puterr(1, "NO OPERATION"));
	CRG->op_info = &op_tab[CRG->op[OPERATION_CODE] - 1];
	byte_ofset = 1 + ((CRG->op_info->arg_count == 1) ? 0 : 1);
	argbyte = ((CRG->op_info->arg_count == 1) ? 0 : CRG->op[ARG_BYTE]);
	i = 0;
	while (i < CRG->op_info->arg_count)
	{
		arg_type = get_arg_type(argbyte);
		if ((arg_type & CRG->op_info->args[i]) != arg_type)
			return (ft_puterr(get_arg_size(CRG->op_info, argbyte), "\033[31mBAD_ARG\033[0m"));
		if (arg_type == T_REG && (CRG->op[byte_ofset] < 0
		|| CRG->op[byte_ofset] > REG_NUMBER))
			return (ft_puterr(get_arg_size(CRG->op_info, argbyte), "\033[31mBAD_REG\033[0m"));
		i++;
		argbyte <<= 2;
		byte_ofset += get_arg_ofset(arg_type, CRG->op_info);
 	}
	return (0);
}
