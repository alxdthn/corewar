/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_o_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:41:17 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 21:19:42 by nalexand         ###   ########.fr       */
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

static void	lfork_print_process(t_list *carriage, t_arg *args, int arg_count, int pos)
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
	((t_carriage *)node->content)->op = 0;
	((t_carriage *)node->content)->position = adr(CURRENT + arg.value);
	ft_lstadd(&((t_core *)core)->carriages, node);
	((t_core *)core)->process_count++;
	if (((t_core *)core)->out == 4)
		lfork_print_process(carriage, &arg, 1, ((t_carriage *)node->content)->position);
	CRG->position = adr(CURRENT + 1 + arg.size);
}
