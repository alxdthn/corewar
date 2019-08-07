/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_a_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 20:01:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:09:55 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	1: live {T_DIR} DSIZE 4
*/

void	cw_live(t_list *carriage)
{
	int		arg;

	arg = ft_reverse_bytes(*((int *)(CRG->op + 1)), sizeof(int));
	if (arg == CRG->reg[0])
	{
		ft_printf("%{gre}s", "LIVE IS DONE!\n");
		CRG->live = 1;
	}
	else
		ft_printf("%{red}s", "LIVE IS NOT DONE!\n");
	ft_printf("arg: %d\n", arg);
	print_operation_info(CRG->op);
}
