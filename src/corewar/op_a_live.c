/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_a_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 20:01:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/13 17:04:50 by nalexand         ###   ########.fr       */
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

static void	print_process(t_core *core, t_list *pc, t_arg *arg)
{
	print_process_header(core, pc);
	ft_printf("%d", arg->value);
	ft_putchar('\n');
}

void		cw_live(void *core, t_list *pc)
{
	t_warrior	**wars;
	t_arg		arg;
	int			i;
	int			new_pos;

	init_args(&arg, pc, 1);
	wars = ((t_core *)core)->warriors;
	i = 0;
	while (wars[i])
	{
		if (arg.value == -wars[i]->nb)
		{
			wars[i]->live = TRUE;
			if (((t_core *)core)->out == 1)
				ft_printf("Player %d (%s) is said to be alive\n", wars[i]->nb, wars[i]->name);
			break ;
		}
		i++;
	}
	new_pos = adr(CURRENT + 1 + arg.size);
	if (((t_core *)core)->out == 4 || ((t_core *)core)->out == 5)
		print_process((t_core *)core, pc, &arg);
	else if (((t_core *)core)->out == 16)
		print_mov(pc, new_pos);
	PC->cycle = 0;
	((t_core *)core)->live_count++;
	PC->position = new_pos;
}
