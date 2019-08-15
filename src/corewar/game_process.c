/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:12:39 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/14 22:28:13 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
			if (((t_core *)core)->out == 16)
				print_mov(pc, new_pos);
			PC->position = new_pos;
		}
		else
			PC->op_info->process(core, pc);
		PC->op_info = NULL;
		PC->op = 0;
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
			print_processes(core, pc, 1);
		pc = pc->next;
	}
}

# define HEIGHT					(MEM_SIZE / 64 + 4)
# define WIDTH					(64 * 3 + 5)

// // // //

static void	draw_border(WINDOW *win)
{
	wattron(win, COLOR_PAIR(GRAY));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(GRAY));
}

void		draw(t_core *core)
{

	draw_border(core->visual.win_arena);
	// wrefresh(core->visual.win_info);
	wrefresh(core->visual.win_arena);
}

void create_frame(t_core *core)
{
	initscr();
	core->visual.win_arena = newwin(HEIGHT, WIDTH + 4, 1, 2);
	core->visual.win_info = newwin(HEIGHT, WIDTH / 4 + 10, 1, WIDTH + 6);
	// werase(core->visual.win_arena);
	// werase(core->visual.win_info);
}

// // // //

void		start_game(t_core *core)
{
	int		cycle_to_die;
	core->flag = 1;

	core->cycle_to_die = CYCLE_TO_DIE;
	cycle_to_die = core->cycle_to_die;
	create_frame(core);
	while (core->pcs)
	{
		if (core->visu_mod)
			show_fight_field(core);
		if (core->cycle_after_start == core->dump
		|| core->cycle_after_start == core->d)
			print_dump(core, 1, 1);
		if (cycle_to_die <= 0)
			game_check(core, &cycle_to_die);
		pc_process(core);
		core->cycle_after_start++;
		cycle_to_die--;
		if (core->out == 2)
			ft_printf("It is now cycle %d\n", core->cycle_after_start);
		draw(core);
	}

}
