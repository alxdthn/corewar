/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_g_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:33:43 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:10:10 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	7: or {T_REG | T_DIR | T_IND}, {T_REG | T_DIR | T_IND}, {T_REG} DSIZE 4
*/

void	cw_or(t_list *carriage)
{
	ft_printf("%{gre}s", "OR IS DONE!\n");
	print_operation_info(CRG->op);
}
