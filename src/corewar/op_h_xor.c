/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_h_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:34:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 20:28:51 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	8: xor {T_REG | T_DIR | T_IND}, {T_REG | T_DIR | T_IND}, {T_REG} DSIZE 4
**
**	По своей сути эта операция полностью аналогична операции and.
**	Только в данном случае «побитовое И» заменяется на «побитовое ИСКЛЮЧАЮЩЕЕ ИЛИ».
*/

static void	xor_print_process(t_core *core, t_list *carriage, t_arg *args)
{
	print_process_header(core, carriage);
	ft_printf("%d %d r%d\n", args[0].value, args[1].value, args[2].value);
}

void		cw_xor(void *core, t_list *carriage)
{
	t_arg	args[3];

	init_args((t_arg *)args, carriage, 3);
	args[0].value = get_operand(args[0], carriage, IDX_MOD);
	args[1].value = get_operand(args[1], carriage, IDX_MOD);
	CRG->reg[args[2].value - 1] = args[0].value ^ args[1].value;
	if (CRG->reg[args[2].value - 1] == 0)
		CRG->carry = TRUE;
	else
		CRG->carry = FALSE;
	if (((t_core *)core)->out == 4)
		xor_print_process((t_core *)core, carriage, (t_arg *)args);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
}
