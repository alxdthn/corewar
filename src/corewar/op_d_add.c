/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_d_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:31:08 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 20:28:18 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	4: add {T_REG}, {T_REG}, {T_REG} DSIZE 4
**
**	Задача операции add:
**	Просуммировать значение из регистра,
**	который был передан как первый аргумент,
**	с значением регистра, который был передан как второй аргумент.
**	Записать полученный результат в регистр, который был передан как третий аргумент.
**	Если полученная сумма, которую мы записали в третий аргумент была равна нулю,
**	то устанавливаем carry в 1. А если сумма была не нулевой — в 0.
*/

static void	print_process(t_core *core, t_list *carriage, t_arg *args)
{
	print_process_header(core, carriage);
	ft_printf("%d %d r%d\n", args[0].value, args[1].value, args[2].value);
}

void		cw_add(void *core, t_list *carriage)
{
	t_arg	args[3];

	init_args((t_arg *)args, carriage, 3);
	CRG->reg[args[2].value - 1]
	= CRG->reg[args[0].value - 1] + CRG->reg[args[1].value - 1];
	if (CRG->reg[args[2].value - 1] == 0)
		CRG->carry = TRUE;
	else
		CRG->carry = FALSE;
	if (((t_core *)core)->out == 4)
		print_process((t_core *)core, carriage, (t_arg *)args);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
}
