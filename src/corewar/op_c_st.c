/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_c_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:30:00 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:24:06 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	3: st {T_REG}, {T_REG | T_IND} DSIZE 4
**
**	Эта операция записывает значение из регистра,
**	который был передан как первый параметр.
**	Зависит от типа второго аргумента:
**
**		Аргумент #2 — T_REG
**		- Из регистра аргумента #1 записываем в регистр аргумента #2.
**
**		Аргумент #2 — T_IND
**		- Определить адрес — текущая позиция + <ВТОРОЙ_АРГУМЕНТ> % IDX_MOD
**		- Записать значение из регистра,
**		который был передан в качестве первого аргумента,
**		в память по полученному адресу.
*/

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;


	ft_printf("%10s > st:   ", CRG->owner->name);
	ofset = print_args((t_arg *)args, 2);
	while (--ofset)
		ft_putchar(' ');
	if (args[1].type == T_IND)
		ft_printf("| set %d from r%d to adr %d\n",
		get_value(CRG->map, adr((CURRENT + args[1].value) % IDX_MOD),
		sizeof(int)), args[0].value,
		adr((CURRENT + args[1].value) % IDX_MOD));
	else
		ft_printf("| set %d from r%d to r%d\n",
		CRG->reg[args[1].value - 1], args[0].value, args[1].value);
}

void	cw_st(void *core, t_list *carriage)
{
	t_arg	args[2];

	init_args((t_arg *)args, carriage, 2);
	if (args[1].type == T_IND)
		set_value_to_adr(carriage, args[1].value, IDX_MOD, CRG->reg[args[0].value - 1]);
	else
		CRG->reg[args[1].value - 1] = CRG->reg[args[0].value - 1];

//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, (t_arg *)args);
//##############################################

	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size);
}
