/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_a_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 20:01:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 03:20:59 by nalexand         ###   ########.fr       */
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

void	cw_live(void *core, t_list *carriage)
{
	int		value;

	value = ft_reverse_bytes(*((int *)(CRG->op + 1)), sizeof(int));
	if (value == CRG->reg[0])
	{
		ft_printf("%{gre}s", "LIVE IS DONE!\n");
		CRG->live = 1;
		CRG->cycle = ((t_core *)core)->cycle_after_start;
		((t_core *)core)->live_count++;
	}
	else
		ft_printf("%{red}s", "LIVE IS NOT DONE!\n");
	ft_printf("value: %d\n", value);
	print_operation_info(CRG->op);
}
