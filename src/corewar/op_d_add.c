/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_d_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:31:08 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:10:05 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	4: add {T_REG}, {T_REG}, {T_REG} DSIZE 4
*/

void	cw_add(t_list *carriage)
{
	ft_printf("%{gre}s", "ADD IS DONE!\n");
	print_operation_info(CRG->op);
}
