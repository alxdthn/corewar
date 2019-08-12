/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_a_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 20:01:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 19:57:58 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	1: live {T_DIR} DSIZE 4
**
**	Засчитывает, что каретка, которая выполняет операцию live, жива.
**	Если указанный в качестве аргумента операции live номер совпадает с номером игрока,
**	то она засчитывает, что это игрок жив.
**	Например, если значение аргумента равно -2, значит игрок с номером 2 жив.
*/

static void	print_process(t_core *core, t_list *carriage, t_arg *arg)
{
	print_process_header(core, carriage);
	ft_printf("%d", arg->value);
	ft_putchar('\n');
}

void		cw_live(void *core, t_list *carriage)
{
	t_warrior	**wars;
	t_arg		arg;
	int			i;

	init_args(&arg, carriage, 1);
	wars = ((t_core *)core)->warriors;
	i = 0;
	while (wars[i])
	{
		if (arg.value == -wars[i]->nb)
			wars[i]->live = TRUE;
		i++;
	}
	CRG->cycle_after_live = 1;
	((t_core *)core)->live_count++;
	if (((t_core *)core)->out == 4)
		print_process((t_core *)core, carriage, &arg);
	CRG->position = adr(CURRENT + 1 + arg.size);
}
