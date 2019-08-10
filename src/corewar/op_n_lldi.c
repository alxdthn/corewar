/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_n_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:40:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 20:24:43 by nalexand         ###   ########.fr       */
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

void	cw_lldi(void *core, t_list *carriage)
{
	/*
	t_core	*ptr;
	int		value;
	int		adr;
	int		a;
	int		b;

	ptr = (t_core *)core;
	a = get_arg_value(carriage, CRG->op, CRG->op[ARG_BYTE], CRG->op);
	b = get_arg_value(carriage, CRG->op + get_arg_ofset(get_arg_type(CRG->op[ARG_BYTE]),
	CRG->op_info), CRG->op[ARG_BYTE] << 2, CRG->op);
	if (get_arg_type(CRG->op[ARG_BYTE]) == T_IND)
		adr = (CRG->position + a + b) % IDX_MOD;
	else
		adr = (CRG->position + a + b);
	value = *((int *)(ptr->map + adr));
	CRG->reg[CRG->op[get_arg_size(CRG->op_info, CRG->op[ARG_BYTE]) - 1] - 1] = value;
	ft_printf("%{gre}s", "LLDI IS DONE!\n");
	print_operation_info(CRG->op);
	*/
}
