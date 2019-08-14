/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_k_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:37:16 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/13 21:08:13 by nalexand         ###   ########.fr       */
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

static void	sti_print_process(t_core *core, t_list *pc, t_arg *args)
{
	int		ofset;

	ofset = print_process_header(core, pc);
	ft_printf("r%d %d %d\n", args[0].value, args[1].value, args[2].value);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| -> store to %d + %d = %d (with pc and mod %d)\n",
	args[1].value, args[2].value,
	args[1].value + args[2].value,
	CURRENT + (args[1].value + args[2].value) % IDX_MOD);
}

void		cw_sti(void *core, t_list *pc)
{
	t_arg	args[3];
	int		new_pos;

//	int	s;
//	if (((t_core *)core)->cycle_after_start == 2809 && PC->nb == 5)
//	{print_map((t_core *)core, 1);
//		ft_putchar('\n');
//		s = 0;
//	}

	init_args((t_arg *)args, pc, 3);
	args[1].value = get_operand(args[1], pc, IDX_MOD);
	args[2].value = get_operand(args[2], pc, IDX_MOD);
	set_value(PC->map, adr(CURRENT + (args[1].value + args[2].value) % IDX_MOD), sizeof(int), PC->reg[args[0].value - 1]);
	new_pos = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
	if (((t_core *)core)->out == 4 || ((t_core *)core)->out == 5)
		sti_print_process((t_core *)core, pc, (t_arg *)args);
	else if (((t_core *)core)->out == 16)
		print_mov(pc, new_pos);
	PC->position = new_pos;

//	if (((t_core *)core)->cycle_after_start == 2809 && PC->nb == 5)
//	{
//		print_map((t_core *)core, 1);
//		ft_putchar('\n');
//	}
}
