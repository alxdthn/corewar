/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_e_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:32:01 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 22:42:35 by nalexand         ###   ########.fr       */
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

static void	print_process(t_core *core, t_list *carriage, t_arg *args)
{
	print_process_header(core, carriage);
	ft_printf("r%d r%d r%d\n", args[0].value, args[1].value, args[2].value);
}

void	cw_sub(void *core, t_list *carriage)
{
	t_arg	args[3];
	int		new_pos;

	init_args((t_arg *)args, carriage, 3);
	CRG->reg[args[2].value - 1]
	= CRG->reg[args[0].value - 1] - CRG->reg[args[1].value - 1];
	if (CRG->reg[args[2].value - 1] == 0)
		CRG->carry = TRUE;
	else
		CRG->carry = FALSE;
	new_pos = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
	if (((t_core *)core)->out == 4)
		print_process((t_core *)core, carriage, (t_arg *)args);
	else if (((t_core *)core)->out == 16)
		print_mov(carriage, new_pos);
	CRG->position = new_pos;
}
