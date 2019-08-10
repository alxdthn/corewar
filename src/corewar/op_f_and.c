/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_f_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:32:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 20:25:49 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	6: and {T_REG | T_DIR | T_IND}, {T_REG | T_DIR | T_IND}, {T_REG} DSIZE 4
**
**	Выполняет операцию «побитовое И» для значений первых двух аргументов 
**	и записывает полученный результат в регистр, переданный в качестве третьего аргумента.
**	Если записанный результат был равен нулю,
**	то значение carry нужно установить равным 1.
**	Если результат был не нулевой, то — равным 0.
**
**		Аргумент #1 / Аргумент #2 — T_REG
**		- Значение берется из регистра, переданного в качестве аргумента.
**
**		Аргумент #1 / Аргумент #2 — T_DIR
**		- В этом случае используется переданное в качестве аргумента числовое значение.
**
**		Аргумент #1 / Аргумент #2 — T_IND
**		- Если тип аргумента T_IND, то необходимо установить адрес, с которого будет считано 4 байта.
**		Адрес определяется следующим образом — текущая позиция + <АРГУМЕНТ> % IDX_MOD.
**		Считанное по этому адресу 4-байтовое число и будет требуемым значением.
*/

static void	cw_and_debug(void *core, t_list *carriage)
{
	/*
	int		a;
	int		b;
	int		value;
	t_core	*ptr;

	ptr = (t_core *)core;
	ft_printf("\n");
	print_operation_info(CRG->op);
	ft_printf("\n");
	ft_printf("arg #1: ");
	a = get_arg_value_debug(carriage, CRG->op, CRG->op[ARG_BYTE], ptr->map);
	ft_printf("arg #2: ");
	b = get_arg_value_debug(carriage, CRG->op + get_arg_ofset(get_arg_type(CRG->op[ARG_BYTE]),
	CRG->op_info), CRG->op[ARG_BYTE] << 2, ptr->map);
	value = a & b;
	CRG->reg[CRG->op[get_arg_size(CRG->op_info, CRG->op[ARG_BYTE]) - 1] - 1] = value;
	if (value)
		CRG->carry = 1;
	else
		CRG->carry = 0;
	ft_printf("res   : r%d\n", value);
	ft_printf("%{gre}s", "AND IS DONE!\n");
	*/
}

void	cw_and(void *core, t_list *carriage)
{
	/*
	t_core	*ptr;
	int		value;
	int		a;
	int		b;

	ptr = (t_core *)core;
	a = get_arg_value(carriage, CRG->op, CRG->op[ARG_BYTE], ptr->map);
	b = get_arg_value(carriage, CRG->op + get_arg_ofset(get_arg_type(CRG->op[ARG_BYTE]),
	CRG->op_info), CRG->op[ARG_BYTE] << 2, ptr->map);
	value = a & b;
	CRG->reg[CRG->op[get_arg_size(CRG->op_info, CRG->op[ARG_BYTE]) - 1] - 1] = value;
	if (value)
		CRG->carry = 1;
	else
		CRG->carry = 0;

	//ft_printf("ORIGIN: a = %hd; b = %hd r = %d\n", a, b, CRG->reg[CRG->op[get_arg_size(CRG->op_info, CRG->op[ARG_BYTE]) - 1] - 1]);

	//cw_and_debug(core, carriage);
	*/
}
