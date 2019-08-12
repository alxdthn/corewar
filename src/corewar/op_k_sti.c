/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_k_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:37:16 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 20:30:44 by nalexand         ###   ########.fr       */
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

static void	sti_print_process(t_core *core, t_list *carriage, t_arg *args)
{
	int		ofset;

	ofset = print_process_header(core, carriage);
	ft_printf("r%d %d %d\n", args[0].value, args[1].value, args[2].value);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| -> store to %d + %d = %d (with pc and mod %d)\n",
	args[1].value, args[2].value,
	args[1].value + args[2].value,
	CURRENT + args[1].value + args[2].value);
}

void		cw_sti(void *core, t_list *carriage)
{
	t_arg	args[3];

	init_args((t_arg *)args, carriage, 3);
	args[1].value = get_operand(args[1], carriage, IDX_MOD);
	args[2].value = get_operand(args[2], carriage, IDX_MOD);
	set_value(CRG->map, adr(CURRENT + (args[1].value + args[2].value) % IDX_MOD), sizeof(int), CRG->reg[args[0].value - 1]);
	if (((t_core *)core)->out == 4)
		sti_print_process((t_core *)core, carriage, (t_arg *)args);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
}
