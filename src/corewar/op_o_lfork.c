/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_o_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:41:17 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 20:05:33 by nalexand         ###   ########.fr       */
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

static void	lfork_print_process(t_core *core, t_list *carriage, t_arg *args, int pos)
{
	print_process_header(core, carriage);
	ft_printf("%d", args->value);
	ft_printf(" (%d)\n", pos);
}

void	cw_lfork(void *core, t_list *carriage)
{
	t_arg	arg;
	t_list	*node;

	if (!(node = ft_lstnew(carriage->content, carriage->content_size)))
		cw_clear_exit((t_core *)core, MEM_ERROR, 2);
	init_args(&arg, carriage, 1);
	((t_carriage *)node->content)->cycle_for_op = 0;
	((t_carriage *)node->content)->op_info = NULL;
	((t_carriage *)node->content)->op = 0;
	((t_carriage *)node->content)->position = adr(CURRENT + arg.value);
	((t_carriage *)node->content)->nb = ++((t_core *)core)->global_process_count;
	((t_core *)core)->current_process_count++;
	ft_lstadd(&((t_core *)core)->carriages, node);
	if (((t_core *)core)->out == 4)
		lfork_print_process((t_core *)core, carriage, &arg, ((t_carriage *)node->content)->position);
	CRG->position = adr(CURRENT + 1 + arg.size);
}
