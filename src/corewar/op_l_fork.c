/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_l_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:38:47 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 22:20:25 by nalexand         ###   ########.fr       */
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

void	fork_print_process(t_list *carriage, t_arg *args, int arg_count, int pos)
{
	int		i;

	ft_printf("P%5d | %s ", CRG->nb, CRG->op_info->op_name);
	i = 0;
	while (i < arg_count)
	{
		if (args[i].type == T_REG)
			ft_putchar('r');
		ft_printf("%d", args[i].value);
		if (i + 1 < arg_count)
			ft_putchar(' ');
		i++;
	}
	ft_printf(" (%d)\n", pos);
}

void	cw_fork(void *core, t_list *carriage)
{
	t_arg	arg;
	t_list	*node;

	if (!(node = ft_lstnew(carriage->content, carriage->content_size)))
		cw_clear_exit((t_core *)core, MEM_ERROR, 2);
	init_args(&arg, carriage, 1);
	((t_carriage *)node->content)->cycle_for_op = 0;
	((t_carriage *)node->content)->op_info = NULL;
	((t_carriage *)node->content)->op = 0;
	((t_carriage *)node->content)->cycle = 0;
	((t_carriage *)node->content)->position = adr(CURRENT + arg.value % IDX_MOD);
	((t_carriage *)node->content)->nb = ++((t_core *)core)->process_count;
	ft_lstadd(&((t_core *)core)->carriages, node);
	if (((t_core *)core)->out == 4)
		fork_print_process(carriage, &arg, 1, ((t_carriage *)node->content)->position);
	CRG->position = adr(CURRENT + 1 + arg.size);
}
