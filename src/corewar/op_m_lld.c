/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_m_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:39:31 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 20:31:38 by nalexand         ###   ########.fr       */
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

static void	lld_print_process(t_core *core, t_list *carriage, t_arg *args, int arg_count)
{
	print_process_header(core, carriage);
	ft_printf("%d r%d\n", args[0].value, args[1].value);
}

void		cw_lld(void *core, t_list *carriage)
{
	t_arg	args[2];

	init_args((t_arg *)args, carriage, 2);
	CRG->reg[args[1].value - 1] = get_operand(args[0], carriage, 0);
	if (CRG->reg[args[1].value - 1] == 0)
		CRG->carry = TRUE;
	else
		CRG->carry = FALSE;
	if (((t_core *)core)->out == 4)
		lld_print_process((t_core *)core, carriage, (t_arg *)args, 2);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size);
}
