/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_b_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:26:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:09:58 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	2: ld {T_DIR | T_REG}, {T_REG} DSIZE 4
*/

void	cw_ld(t_list *carriage)
{
	ft_printf("%{gre}s", "LD IS DONE!\n");
	print_operation_info(CRG->op);
}
