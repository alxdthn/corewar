/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_h_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:34:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 20:25:25 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	8: xor {T_REG | T_DIR | T_IND}, {T_REG | T_DIR | T_IND}, {T_REG} DSIZE 4
**
**	По своей сути эта операция полностью аналогична операции and.
**	Только в данном случае «побитовое И» заменяется на «побитовое ИСКЛЮЧАЮЩЕЕ ИЛИ».
*/

void	cw_xor(void *core, t_list *carriage)
{
	/*
	t_core	*ptr;
	int		value;
	int		a;
	int		b;

	ptr = (t_core *)core;
	a = get_arg_value(carriage, CRG->op, CRG->op[ARG_BYTE], ptr->map);
	b = get_arg_value(carriage, CRG->op + get_arg_ofset(get_arg_type(CRG->op[ARG_BYTE]),
	CRG->op_info), CRG->op[ARG_BYTE] << 2, ptr->map);
	value = a & b;
	CRG->reg[CRG->op[get_arg_size(CRG->op_info, CRG->op[ARG_BYTE]) - 1] - 1] = value;
	if (value)
		CRG->carry = 1;
	else
		CRG->carry = 0;

	ft_printf("%{gre}s", "OR IS DONE!\n");
	print_operation_info(CRG->op);
	*/
}
