/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_l_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:38:47 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:24:58 by nalexand         ###   ########.fr       */
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

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;

	ft_printf("%10s > fork: ", CRG->owner->name);
	ofset = print_args(args, 1);
	while (--ofset)
		ft_putchar(' ');
	ft_printf("| no ifno\n");
}

void	cw_fork(void *core, t_list *carriage)
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
	((t_carriage *)node->content)->position = adr(arg.value % IDX_MOD);
	ft_lstadd(&((t_core *)core)->carriages, node);
	CRG->position = adr(CURRENT + 1 + arg.size);
//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, &arg);
//##############################################
}
