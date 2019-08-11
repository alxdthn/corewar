/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_a_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 20:01:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:23:25 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	1: live {T_DIR} DSIZE 4
**
**	Засчитывает, что каретка, которая выполняет операцию live, жива.
**	Если указанный в качестве аргумента операции live номер совпадает с номером игрока,
**	то она засчитывает, что это игрок жив.
**	Например, если значение аргумента равно -2, значит игрок с номером 2 жив.
*/

static void	debug_info(t_list *carriage, t_arg *arg)
{
	int		ofset;

	ft_printf("%10s > live: ", CRG->owner->name);
	ofset = print_args(arg, 1);
	while (--ofset)
		ft_putchar(' ');
	if (CRG->live)
		ft_printf("| player №%d %s "GRE"live"EOC"\n", CRG->owner->nb, CRG->owner->name);
	else
		ft_printf("| player №%d %s "RED"not live"EOC"\n", CRG->owner->nb, CRG->owner->name);
}

void	cw_live(void *core, t_list *carriage)
{
	t_arg	arg;

	init_args(&arg, carriage, 1);
	if (arg.value == -CRG->owner->nb)
	{
		CRG->live = TRUE;
		CRG->cycle = ((t_core *)core)->cycle_after_start;
		((t_core *)core)->live_count++;
	}

//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, &arg);
//##############################################

	CRG->position = adr(CURRENT + 1 + arg.size);
}
