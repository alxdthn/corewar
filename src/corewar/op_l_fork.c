/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_l_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:38:47 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/13 17:15:26 by nalexand         ###   ########.fr       */
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

void	fork_print_process(t_core *core, t_list *pc, t_arg *args, int pos)
{
	print_process_header(core, pc);
	ft_printf("%d", args->value);
	ft_printf(" (%d)\n", pos);
}

void	cw_fork(void *core, t_list *pc)
{
	t_arg		arg;
	t_list		*node;
	int			new_pos;

	if (!(node = ft_lstnew(pc->content, sizeof(t_pc))))
		cw_clear_exit((t_core *)core, MEM_ERROR, 2);
	init_args(&arg, pc, 1);
	((t_pc *)node->content)->cycle_for_op = 0;
	((t_pc *)node->content)->op_info = NULL;
	((t_pc *)node->content)->op = 0;
	((t_pc *)node->content)->position = adr(CURRENT + arg.value % IDX_MOD);
	((t_pc *)node->content)->nb = ++((t_core *)core)->global_process_count;
	((t_core *)core)->current_process_count++;
	ft_lstadd(&((t_core *)core)->pcs, node);
	new_pos = adr(CURRENT + 1 + arg.size);
	if (((t_core *)core)->out == 4 || ((t_core *)core)->out == 5)
		fork_print_process((t_core *)core, pc, &arg, ((t_pc *)node->content)->position);
	else if (((t_core *)core)->out == 16)
		print_mov(pc, new_pos);
	PC->position = new_pos;
}
