/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_n_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:40:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 22:48:23 by nalexand         ###   ########.fr       */
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

static void	lldi_print_process(t_core *core, t_list *carriage, t_arg *args)
{
	int		ofset;

	ofset = print_process_header(core, carriage);
	ft_printf("%d %d r%d\n", args[0].value, args[1].value, args[2].value);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| -> load from %d + %d = %d (with pc %d)\n",
	args[0].value, args[1].value,
	args[0].value + args[1].value,
	CURRENT + args[0].value + args[1].value);
}

void	cw_lldi(void *core, t_list *carriage)
{
	t_arg	args[3];
	int		new_pos;

	init_args((t_arg *)args, carriage, 3);
	args[0].value = get_operand(args[0], carriage, IDX_MOD);
	args[1].value = get_operand(args[1], carriage, IDX_MOD);
	CRG->reg[args[2].value - 1] = get_value_from_adr(carriage, args[0].value + args[1].value, 0);
	if (CRG->reg[args[2].value - 1] == 0)
		CRG->carry = TRUE;
	else
		CRG->carry = FALSE;
	new_pos = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
	if (((t_core *)core)->out == 4)
		lldi_print_process((t_core *)core, carriage, (t_arg *)args);
	else if (((t_core *)core)->out == 16)
		print_mov(carriage, new_pos);
	CRG->position = new_pos;
}
