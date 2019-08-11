/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_m_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:39:31 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:25:03 by nalexand         ###   ########.fr       */
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

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;

	ft_printf("%10s > lld:   ", CRG->owner->name);
	ofset = print_args(args, 1);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| no ifno\n");
}

void	cw_lld(void *core, t_list *carriage)
{
	t_arg	args[2];

	init_args((t_arg *)args, carriage, 2);
	CRG->reg[args[1].value - 1] = get_operand(args[0], carriage, 0);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size);
//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, (t_arg *)args);
//##############################################
}
