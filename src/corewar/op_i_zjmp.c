/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_i_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:35:06 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:10:15 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	9: zjmp {T_DIR} DSIZE 2
*/

void	cw_zjmp(t_list *carriage)
{
	ft_printf("%{gre}s", "ZJMP IS DONE!\n");
	print_operation_info(CRG->op);
}
