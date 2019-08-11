/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_p_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:41:59 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:25:17 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	16: aff {T_REG} DSIZE 4
**
**	Эта операция берет значение из регистра,
**	который был передан в качестве единственного аргумента.
**	Приводит его к типу char. И выводит на экран как ASCII-символ.
**
**	В оригинальной виртуальной машине corewar по умолчанию
**	режим отображения вывода операции aff выключен.
**	Чтобы его включить нужно воспользоваться флагом -a.
*/

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;

	ft_printf("%10s > aff:   ", CRG->owner->name);
	ofset = print_args(args, 1);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| no ifno\n");
}

void	cw_aff(void *core, t_list *carriage)
{
	t_arg	arg;

	init_args(&arg, carriage, 1);
	write(1, &CRG->reg[arg.value - 1], 1);
	CRG->position = adr(CURRENT + 1 + arg.size);
//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, &arg);
//##############################################
}
