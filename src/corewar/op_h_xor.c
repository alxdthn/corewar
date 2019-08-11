/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_h_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:34:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 19:28:15 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	8: xor {T_REG | T_DIR | T_IND}, {T_REG | T_DIR | T_IND}, {T_REG} DSIZE 4
**
**	По своей сути эта операция полностью аналогична операции and.
**	Только в данном случае «побитовое И» заменяется на «побитовое ИСКЛЮЧАЮЩЕЕ ИЛИ».
*/

static void	xor_print_process(t_list *carriage, t_arg *args, int arg_count)
{
	int		i;

	ft_printf("P%5d | %s ", CRG->nb, CRG->op_info->op_name);
	i = 0;
	while (i < arg_count)
	{
		if (args[i].type == T_REG && i > 1)
			ft_putchar('r');
		ft_printf("%d", (i < 2) ? CRG->reg[args[i].value - 1] : args[i].value);
		if (i + 1 < arg_count)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void		cw_xor(void *core, t_list *carriage)
{
	t_arg	args[3];
	int		a;
	int		b;

	init_args((t_arg *)args, carriage, 3);
	a = get_operand(args[0], carriage, IDX_MOD);
	b = get_operand(args[1], carriage, IDX_MOD);
	CRG->reg[args[2].value - 1] = a ^ b;
	if (CRG->reg[args[2].value - 1] == 0)
		CRG->carry = TRUE;
	else
		CRG->carry = FALSE;
	if (((t_core *)core)->out == 4)
		xor_print_process(carriage, (t_arg *)args, 3);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
}
