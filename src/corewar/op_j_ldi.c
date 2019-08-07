/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_j_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:35:52 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:10:19 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*	
**	10: ldi {T_REG | T_DIR | T_IND}, {T_REG | T_DIR}, T_REG DSIZE 2
*/

void	cw_ldi(t_list *carriage)
{
	ft_printf("%{gre}s", "LDI IS DONE!\n");
	print_operation_info(CRG->op);
}
