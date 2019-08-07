/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_p_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:41:59 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:10:34 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	16: aff {T_REG} DSIZE 4
*/

void	cw_aff(t_list *carriage)
{
	ft_printf("%{gre}s", "AFF IS DONE!\n");
	print_operation_info(CRG->op);
}
