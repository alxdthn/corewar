/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_m_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:39:31 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 20:24:50 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	13: lld {T_DIR | T_IND}, {T_REG} DSIZE 4
**
**	Записывает значение, полученное из первого аргумента,
**	в регистр, переданный как второй аргумент.
**
**	Различие между ld состоит в применении усечения по модулю.
**	Если первый аргумент имеет тип T_IND,
**	то в этой операции мы будем считывать 4 байта
**	значения по адресу — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ>.
**	Не применяя усечение по модулю.
*/

void	cw_lld(void *core, t_list *carriage)
{
	/*
	int		byte_ofset;
	int		value;
	t_core	*ptr;

	ptr = (t_core *)core;
	byte_ofset = 0;
	if (get_arg_type(CRG->op[ARG_BYTE]) == T_DIR)
	{
		byte_ofset = 5;
		value = ft_reverse_bytes(*((int *)(CRG->op + 2)), sizeof(int));
	}
	else
	{
		byte_ofset = 3;
		value = ft_reverse_bytes(*(int *)(ptr->map + CRG->position
		+ ft_reverse_bytes(*((short *)(CRG->op + 2)), sizeof(short))), sizeof(int));
	}
	CRG->reg[CRG->op[byte_ofset + 1] - 1] = value;
	if (value == 0)
		CRG->carry = 1;
	else
		CRG->carry = 0;
	ft_printf("%{gre}s", "LLD IS DONE!\n");
	print_operation_info(CRG->op);
	*/
}
