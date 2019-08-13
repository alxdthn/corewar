/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:12:39 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/13 22:04:42 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	introduce(t_core *core)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (core->players[i])
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		core->players[i]->nb, core->players[i]->code_size,
		core->players[i]->name, core->players[i]->comment);
		i++;
	}
}

static void	validate_op_code(t_core *core, t_list *pc)
{
	int		new_pos;

	PC->op = BYTE(CURRENT);
	if (PC->op > 0 && PC->op < 17)
	{
		PC->op_info = &g_op_tab[PC->op - 1];
		PC->cycle_for_op = PC->op_info->cycle;
	}
	else
	{
		new_pos = adr(CURRENT + 1);
		PC->op = 0;
		if (((t_core *)core)->out == 16)
			print_mov(pc, new_pos);
		PC->position = new_pos;
	}
}

static void	solve_operation(t_core *core, t_list *pc)
{
	int		new_pos;
	int		ofset;

	PC->cycle_for_op--;
	if (PC->cycle_for_op == 0)
	{
		if ((ofset = validate_operation(pc)))
		{
			new_pos = adr(CURRENT + ofset);
			PC->op = 0;
			PC->op_info = NULL;
			if (((t_core *)core)->out == 16)
				print_mov(pc, new_pos);
			PC->position = new_pos;
		}
		else
		{
			PC->op_info->process(core, pc);
			PC->op = 0;
			PC->op_info = NULL;
		}
	}
}

static void	pc_process(t_core *core)
{
	t_list	*pc;

	pc = core->pcs;
	while (pc)
	{
		PC->cycle++;
		if (!PC->op)
			validate_op_code(core, pc);
		if (PC->op_info)
			solve_operation(core, pc);
		if (PC->nb == core->print_pc)
			print_pcs(core, pc, 1);
		pc = pc->next;
	}
}

void		start_game(t_core *core)
{
	int		cycle_to_die;
	int		test;

	core->cycle_to_die = CYCLE_TO_DIE;
	cycle_to_die = core->cycle_to_die;
	introduce(core);
	if (core->print_pc)
		ft_printf(" g_cycle | number | position | live_cycle |"\
		" op_cycle | carry | operation | registers\n");
	while (core->pcs)
	{
		if (core->cycle_after_start == core->dump)
			print_dump(core, 1, 1);
		if (cycle_to_die <= 0)
			game_check(core, &cycle_to_die);
		pc_process(core);
		core->cycle_after_start++;
		cycle_to_die--;
		if (core->out == 2)
			ft_printf("It is now cycle %d\n", core->cycle_after_start);
	}
}
