/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_o_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:41:17 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/14 22:52:21 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	15: lfork {T_DIR} DSIZE 2
**
**	По своей сути эта операция аналогична операции fork.
**	За исключением того факта,
**	что новая каретка в этом случае создается по адресу:
**		текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ>.
**	В операции lfork усечение по модулю делать не нужно.
*/

static void	lfork_print_process(t_core *core, t_list *pc, t_arg *args)
{
	print_process_header(core, pc);
	ft_printf("%d", args->value);
	ft_printf(" (%d)\n", PC->position + args->value);
}

void		cw_lfork(void *core, t_list *pc)
{
	t_arg	arg;
	t_list	*node;

	if (!(node = ft_lstnew(pc->content, sizeof(t_pc))))
		cw_clear_exit((t_core *)core, MEM_ERROR, 2);
	init_args(&arg, pc, 1);
	((t_pc *)node->content)->cycle_for_op = 0;
	((t_pc *)node->content)->op_info = NULL;
	((t_pc *)node->content)->op = 0;
	((t_pc *)node->content)->position = adr(CURRENT + arg.value);
	if (((t_core *)core)->visu_mod
	&& ((t_core *)core)->visual.map[((t_pc *)node->content)->position] < 14)
		((t_core *)core)->visual.map[((t_pc *)node->content)->position] += 5;
	((t_pc *)node->content)->nb = ++((t_core *)core)->global_process_count;
	((t_core *)core)->current_process_count++;
	ft_lstadd(&((t_core *)core)->pcs, node);
	if (((t_core *)core)->out == 4 || ((t_core *)core)->out == 5)
		lfork_print_process((t_core *)core, pc, &arg);
	mov_pc((t_core *)core, pc, adr(CURRENT + 1 + arg.size));
}
