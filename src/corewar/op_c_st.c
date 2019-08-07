/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_c_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:30:00 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:10:03 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	3: st {T_REG}, {T_REG | T_IND} DSIZE 4
*/

void	cw_st(t_list *carriage)
{
	ft_printf("%{gre}s", "ST IS DONE!\n");
	print_operation_info(CRG->op);
}
