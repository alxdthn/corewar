/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_h_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:34:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:24:35 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	8: xor {T_REG | T_DIR | T_IND}, {T_REG | T_DIR | T_IND}, {T_REG} DSIZE 4
**
**	По своей сути эта операция полностью аналогична операции and.
**	Только в данном случае «побитовое И» заменяется на «побитовое ИСКЛЮЧАЮЩЕЕ ИЛИ».
*/

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;
	int		i;

	ft_printf("%10s > xor:   ", CRG->owner->name);
	ofset = print_args(args, 3);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("|");
	i = 0;
	while (i < 2)
	{
		if (args[i].type == T_REG)
		{
			ft_printf(" %d(r%d)", CRG->reg[args[i].value - 1], args[i].value);
			i++;
		}
		else if (args[i].type == T_DIR)
			ft_printf(" %d", args[i++].value);
		else
		{
			ft_printf(" %d(adr %d)",
			get_value_from_adr(carriage, args[i].value, IDX_MOD),
			adr((CURRENT + args[i].value) % IDX_MOD));
			i++;
		}
		if (i == 1)
			ft_printf(" ^");
	}
	ft_printf(" = %d(r%d)\n", CRG->reg[args[2].value - 1], args[2].value);
}

void		cw_xor(void *core, t_list *carriage)
{
	t_arg	args[3];
	int		a;
	int		b;

	init_args((t_arg *)args, carriage, 3);
	a = get_operand(args[0], carriage, IDX_MOD);
	b = get_operand(args[1], carriage, IDX_MOD);
	CRG->reg[args[2].value - 1] = a ^ b;

//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, (t_arg *)args);
//##############################################

	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
}
