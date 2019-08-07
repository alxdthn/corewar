/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_f_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:32:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:10:09 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	6: and {T_REG | T_DIR | T_IND}, {T_REG | T_DIR | T_IND}, {T_REG} DSIZE 4
*/

void	cw_and(t_list *carriage)
{
	ft_printf("%{gre}s", "AND IS DONE!\n");
	print_operation_info(CRG->op);
}
