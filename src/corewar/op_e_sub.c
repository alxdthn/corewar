/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_e_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:32:01 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:24:16 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	5: sub {T_REG}, {T_REG}, {T_REG} DSIZE 4
**
**	Задачи:
**	- От значения регистра, переданного в качестве первого аргумента,
**	отнять значение регистра, который был передан в качестве второго аргумента.
**	Полученный результат записать в регистр, который был передан в качестве третьего аргумента.
**	Если записанный результат был равен нулю,
**	то значение carry сделать равным 1.
**	Если результат был не нулевой, то сделать равным 0.
*/

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;

	ft_printf("%10s > sub:  ", CRG->owner->name);
	ofset = print_args(args, 3);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| %d(r%d) - %d(r%d) = %d(r%d)\n",
	CRG->reg[args[0].value - 1], args[0].value,
	CRG->reg[args[1].value - 1], args[1].value,
	CRG->reg[args[2].value - 1], args[2].value);
}

void	cw_sub(void *core, t_list *carriage)
{
	t_arg	args[3];

	init_args((t_arg *)args, carriage, 3);
	CRG->reg[args[2].value - 1]
	= CRG->reg[args[0].value - 1] - CRG->reg[args[1].value - 1];
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
