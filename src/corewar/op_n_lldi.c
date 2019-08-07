/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_n_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:40:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:10:29 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	14: lldi {T_REG | T_DIR | T_IND}, {T_REG | T_DIR}, {T_REG} DSIZE 2
*/

void	cw_lldi(t_list *carriage)
{
	ft_printf("%{gre}s", "LLDI IS DONE!\n");
	print_operation_info(CRG->op);
}
