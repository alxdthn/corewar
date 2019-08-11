/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_k_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:37:16 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 20:02:56 by nalexand         ###   ########.fr       */
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

static void	sti_print_process(t_list *carriage, t_arg *args, int a, int b)
{
	int		i;

	ft_printf("P%5d | %s ", CRG->nb, CRG->op_info->op_name);
	i = 0;
	while (i < 3)
	{
		if (args[i].type == T_REG && !i)
			ft_putchar('r');
		ft_printf("%d", (!i) ? args[i].value : CRG->reg[args[i].value - 1]);
		if (i + 1 < 3)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", a, b, a + b, CURRENT + a + b);
}

void		cw_sti(void *core, t_list *carriage)
{
	t_arg	args[3];
	int		a;
	int		b;

	init_args((t_arg *)args, carriage, 3);
	a = get_operand(args[1], carriage, IDX_MOD);
	b = get_operand(args[2], carriage, IDX_MOD);
	set_value(CRG->map, adr(CURRENT + (a + b) % IDX_MOD), sizeof(int), CRG->reg[args[0].value - 1]);
	if (((t_core *)core)->out == 4)
		sti_print_process(carriage, (t_arg *)args, a, b);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
}
