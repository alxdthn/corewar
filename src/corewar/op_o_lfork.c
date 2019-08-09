/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_o_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:41:17 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 04:07:52 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	15: lfork {T_DIR} DSIZE 2
**
**	По своей сути эта операция аналогична операции fork.
**	За исключением того факта, что новая каретка в этом случае создается по адресу: 
**		текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ>.
**	В операции lfork усечение по модулю делать не нужно.
*/

void	cw_lfork(void *core, t_list *carriage)
{
	t_core	*ptr;
	t_list	*node;

	ptr = (t_core *)core;
	if (!(node = ft_lstnew(carriage->content, carriage->content_size)))
		cw_clear_exit(ptr, MEM_ERROR, 2);
	((t_carriage *)node->content)->cycle = 0;
	((t_carriage *)node->content)->cycle_for_op = 0;
	((t_carriage *)node->content)->live = 0;
	((t_carriage *)node->content)->ofset = 0;
	((t_carriage *)node->content)->op = NULL;
	((t_carriage *)node->content)->op_info = NULL;
	((t_carriage *)node->content)->position
	= ft_reverse_bytes(*((short *)(CRG->op + 1)), sizeof(short));
	ft_lstadd(&ptr->carriages, node);
	ft_printf("%{gre}s", "LFORK IS DONE!\n");
	print_operation_info(CRG->op);
}
