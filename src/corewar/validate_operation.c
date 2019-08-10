/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_operation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:39:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/10 17:18:11 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Валидация операции, возвращает количествой байт
**	на которые должна перейти каретка в случае невалидной операции.
**	(Вывод ошибок временный)
*/

int		validate_operation(t_core *core, t_list *carriage)
{
	int		i;
	int		byte_ofset;
	char	argbyte;
	char	arg_type;

	if (POS(CURRENT) < 1 || POS(CURRENT) > 16)
		return (1);
	if (CRG->op_info != &op_tab[POS(CURRENT) - 1])
		CRG->cycle_for_op = 0;
	CRG->op_info = &op_tab[POS(CURRENT) - 1];
	byte_ofset = 1 + ARG_TYPE;
	argbyte = ((ARG_TYPE) ? POS(ARG_BYTE) : OPER_ARGS[0]);
	i = 0;
	while (i < CRG->op_info->arg_count)
	{
		arg_type = get_arg_type(argbyte);
		if ((arg_type & OPER_ARGS[i]) != arg_type)
			return (ft_puterr(get_function_size(argbyte, CRG->op_info), "\033[31mBAD_ARG\033[0m"));
		if (arg_type == T_REG && (POS(CURRENT + byte_ofset) < 0
		|| POS(CURRENT + byte_ofset) > REG_NUMBER))
			return (ft_puterr(get_function_size(argbyte, CRG->op_info), "\033[31mBAD_REG\033[0m"));
		i++;
		argbyte <<= 2;
		byte_ofset += get_arg_ofset(arg_type, CRG->op_info);
 	}
	return (0);
}
