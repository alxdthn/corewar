/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_m_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:39:31 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 20:10:24 by nalexand         ###   ########.fr       */
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

static void	lld_print_process(t_list *carriage, t_arg *args, int arg_count)
{
	int		i;

	ft_printf("P%5d | %s ", CRG->nb, CRG->op_info->op_name);
	i = 0;
	while (i < arg_count)
	{
		if (args[i].type == T_REG)
			ft_putchar('r');
		ft_printf("%d", (!i) ? CRG->reg[args[1].value - 1] : args[i].value);
		if (i + 1 < arg_count)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
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
		lld_print_process(carriage, (t_arg *)args, 2);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size);
}
