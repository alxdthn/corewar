/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_j_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:35:52 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 03:12:27 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*	
**	10: ldi {T_REG | T_DIR | T_IND}, {T_REG | T_DIR}, {T_REG} DSIZE 2
**
**	Данная операция записывает значение в регистр, 
**	который был ей передан как третий параметр.
**	Значением, которая она записывает, являются 4 байта.
**	Эти 4 байта она считывает по адресу,
**	который формируется по следующему принципу:
**	текущая позиция + (<ЗНАЧЕНИЕ_ПЕРВОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА>) % IDX_MOD.
**
**	Поскольку операция может принимать разные типы
**	первого и второго аргументов,
**	рассмотрим способ получения значения для каждого типа:
**
**		Аргумент #1 / Аргумент #2 — T_REG
**		- Значение содержится в регистре, который был передан в качестве параметра.
**
**		Аргумент #1 / Аргумент #2 — T_DIR
**		- В данном случае у нас аргумент уже содержит свое значение.
**
**		Аргумент #1 — T_IND
**		- Чтобы получить значение этого аргумента,
**		нужно считать 4 байта по адресу — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
*/

void	cw_ldi(void *core, t_list *carriage)
{
	t_core	*ptr;
	int		value;
	int		adr;
	int		a;
	int		b;

	ptr = (t_core *)core;
	a = get_arg_value(carriage, CRG->op, CRG->op[ARG_BYTE], ptr->map);
	b = get_arg_value(carriage, CRG->op + get_arg_ofset(get_arg_type(CRG->op[ARG_BYTE]),
	CRG->op_info), CRG->op[ARG_BYTE] << 2, ptr->map);
	adr = CRG->position + a + b % IDX_MOD;
	value = *((int *)(ptr->map + adr));
	CRG->reg[CRG->op[get_arg_size(CRG->op_info, CRG->op[ARG_BYTE]) - 1] - 1] = value;

	ft_printf("%{gre}s", "LDI IS DONE!\n");
	print_operation_info(CRG->op);
}
