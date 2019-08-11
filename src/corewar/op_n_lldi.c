/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_n_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:40:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:25:08 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	14: lldi {T_REG | T_DIR | T_IND}, {T_REG | T_DIR}, {T_REG} DSIZE 2
**
**	По своей сути данная операция аналогична операции ldi.
**	Она записывает значение в регистр, который был передан ей как третий параметр.
**	Значением, которая эта операция записывает, являются считанные 4 байта.
**	Они считываются по адресу, который формируется по следующему принципу:
**		текущая позиция + (<ЗНАЧЕНИЕ_ПЕРВОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА>).
**
**	В отличие от операции ldi в этом случае при формировании адреса не нужно делать усечение по модулю IDX_MOD.
**	Для аргументов типа T_IND все остается по старому
**	Если в качестве первого или второго аргумента мы получаем аргумент типа T_IND,
**	то все так же считываем 4 байта значения по адресу: 
**		текущая позиция + <АРГУМЕНТ> % IDX_MOD.
**	Здесь усечение по модулю сохраняется.
*/

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;

	ft_printf("%10s > lldi:  ", CRG->owner->name);
	ofset = print_args(args, 1);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| no ifno\n");
}

void	cw_lldi(void *core, t_list *carriage)
{
	t_arg	args[3];
	int		a;
	int		b;

	init_args((t_arg *)args, carriage, 3);
	a = get_operand(args[0], carriage, IDX_MOD);
	b = get_operand(args[1], carriage, IDX_MOD);
	CRG->reg[args[2].value - 1] = get_value_from_adr(carriage, a + b, 0);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, (t_arg *)args);
//##############################################
}
