/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_e_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:32:01 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:10:07 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	5: sub {T_REG}, {T_REG}, {T_REG} DSIZE 4
*/

void	cw_sub(t_list *carriage)
{
	int		arg;

	ft_printf("%{gre}s", "SUB IS DONE!\n");
	print_operation_info(CRG->op);
}
