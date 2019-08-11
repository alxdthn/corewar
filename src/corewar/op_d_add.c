/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_d_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:31:08 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:24:11 by nalexand         ###   ########.fr       */
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

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;

	ft_printf("%10s > add:  ", CRG->owner->name);
	ofset = print_args((t_arg *)args, 3);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| %d(r%d) + %d(r%d) = %d(r%d)\n",
	CRG->reg[args[0].value - 1], args[0].value,
	CRG->reg[args[1].value - 1], args[1].value,
	CRG->reg[args[2].value - 1], args[2].value);
}

void	cw_add(void *core, t_list *carriage)
{
	t_arg	args[3];

	init_args((t_arg *)args, carriage, 3);
	CRG->reg[args[2].value - 1]
	= CRG->reg[args[0].value - 1] + CRG->reg[args[1].value - 1];
	if (CRG->reg[args[2].value - 1])
		CRG->carry = TRUE;
	else
		CRG->carry = FALSE;

//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, (t_arg *)args);
//##############################################

	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
}
