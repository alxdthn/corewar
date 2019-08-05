/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_warriors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:41:13 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/05 19:00:55 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	set_start_position(t_core *core)
{
	int			start;
	int			i;

	i = 0;
	start = 0;
	while (core->warriors[i])
	{
		core->warriors[i++]->start_position = start;
		start += MEM_SIZE / core->war_count;
	}
}

void		init_warriors(t_core *core)
{
	t_list		*input;
	t_warrior	*new;
	int			nb;
	int			i;

	input = core->input;
	nb = core->war_count;
	i = nb;
	while (input)
	{
		if (!(new = (t_warrior *)malloc(sizeof(t_warrior))))
			cw_clear_exit(core, MEM_ERROR, 2);
		new->nb = nb--;
		new->name = STR(input) + NAME_OFSET;
		new->comment = STR(input) + COMMENT_OFSET;
		new->code_size = mem_rev(*((int *)input->content + CODE_SIZE_OFSET));
		new->exec_code = STR(input) + EXEC_CODE_OFSET;
		core->warriors[--i] = new;
		input = input->next;
	}
	set_start_position(core);
}
