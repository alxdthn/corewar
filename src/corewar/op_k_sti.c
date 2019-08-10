/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_k_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:37:16 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 20:25:05 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	11: sti {T_REG}, {T_REG | T_DIR | T_IND}, {T_REG | T_DIR} DSIZE 2
**
**	Эта операция записывает значение регистра,
**	переданного в качестве первого параметра,
**	по адресу: текущая позиция + (<ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ТРЕТЕГО_АРГУМЕНТА>) % IDX_MOD.
*/

void	cw_sti(void *core, t_list *carriage)
{
	/*
	t_core	*ptr;
	int		adr;
	int		a;
	int		b;

	ptr = (t_core *)core;
	a = get_arg_value(carriage, CRG->op, CRG->op[ARG_BYTE] << 2, ptr->map);
	b = get_arg_value(carriage, CRG->op + get_arg_ofset(get_arg_type(CRG->op[ARG_BYTE]),
	CRG->op_info), CRG->op[ARG_BYTE] << 4, ptr->map);
	adr = CRG->position + a + b % IDX_MOD;
	*((int *)(ptr->map + adr))
	= CRG->reg[CRG->op[get_arg_size(CRG->op_info, CRG->op[ARG_BYTE]) - 1] - 1];

	ft_printf("%{gre}s", "STI IS DONE!\n");
	print_operation_info(CRG->op);
	*/
}
