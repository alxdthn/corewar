/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_l_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:38:47 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 20:24:57 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	12: fork {T_DIR} DSIZE 2
**
**	Операция fork делает копию каретки.
**	И эту копию размещает по адресу <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
**		- Значения всех регистров
**		- Значение carry
**		- Номер цикла, в котором в последний раз выполнялась операция live
**		- И кое-что еще, но об этом позже.
*/

void	cw_fork(void *core, t_list *carriage)
{
	/*
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
	= ft_reverse_bytes(*((short *)(CRG->op + 1)), sizeof(short)) % IDX_MOD;
	ft_lstadd(&ptr->carriages, node);
	ft_printf("%{gre}s", "FORK IS DONE!\n");
	print_operation_info(CRG->op);
	*/
}
