/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_k_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:37:16 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:24:53 by nalexand         ###   ########.fr       */
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

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;

	ft_printf("%10s > sti:  ", CRG->owner->name);
	ofset = print_args(args, 1);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| no ifno\n");
}

void		cw_sti(void *core, t_list *carriage)
{
	t_arg	args[3];
	int		a;
	int		b;

	init_args((t_arg *)args, carriage, 3);
	a = get_operand(args[1], carriage, IDX_MOD);
	b = get_operand(args[2], carriage, IDX_MOD);
	set_value_to_adr(carriage, a + b, IDX_MOD, CRG->reg[args[0].value - 1]);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, (t_arg *)args);
//##############################################
}
