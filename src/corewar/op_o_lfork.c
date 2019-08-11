/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_o_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:41:17 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:25:13 by nalexand         ###   ########.fr       */
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

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;

	ft_printf("%10s > lfork: ", CRG->owner->name);
	ofset = print_args(args, 1);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| no ifno\n");
}

void	cw_lfork(void *core, t_list *carriage)
{
	t_arg	arg;
	t_list	*node;

	if (!(node = ft_lstnew(carriage->content, carriage->content_size)))
		cw_clear_exit((t_core *)core, MEM_ERROR, 2);
	init_args(&arg, carriage, 1);
	((t_carriage *)node->content)->cycle = 0;
	((t_carriage *)node->content)->cycle_for_op = 0;
	((t_carriage *)node->content)->live = 0;
	((t_carriage *)node->content)->op_info = NULL;
	((t_carriage *)node->content)->position = adr(arg.value);
	ft_lstadd(&((t_core *)core)->carriages, node);
	CRG->position = adr(CURRENT + 1 + arg.size);
//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, &arg);
//##############################################
}
