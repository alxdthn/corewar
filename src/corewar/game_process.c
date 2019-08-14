/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:12:39 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/13 23:40:48 by nalexand         ###   ########.fr       */
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
			print_processes(core, pc, 1);
		pc = pc->next;
	}
}

// ****************** Visual ****************** //

int				is_carry_here(t_core *core, int i)
{
    t_list	    *pc;
    int			j;

    j = 0;
    pc = core->pcs;
    while (pc)
    {
        if (pc->content_size == i)
            return (j);
        j++;
        pc = pc->next;
    }
    return (-1);
}
//
#define MAX_COLOR_NUM 4
//
static void		print_arena_content(t_core *core, int i, int y, int x)
{
    int id;

    id = is_carry_here(core, i);
    if (id == -2)
    {
        attron(COLOR_PAIR(3));
        mvprintw(y, x, "%02x", core->map[i]);
        attroff(COLOR_PAIR(3));
    }
    if (id != -1)
    {
        attron(COLOR_PAIR(id % MAX_COLOR_NUM));
        mvprintw(y, x, "%02x", core->map[i]);
        attroff(COLOR_PAIR(id % MAX_COLOR_NUM));
    }
    else
    {
        attron(COLOR_PAIR(9));
        mvprintw(y, x, "%02x", core->map[i]);
        attroff(COLOR_PAIR(9));
    }
}

void			print_arena_visu(t_core *core)
{
    int		i;
    int		x;
    int		y;

    i = 0;
    x = 1;
    y = 1;
    while (i < MEM_SIZE)
    {
        print_arena_content(core, i, y, x);
        x = x + 2;
        mvprintw(y, x, " ");
        x++;
        if (i && (i + 1) % 64 == 0)
        {
            y++;
            x = 1;
        }
        i++;
    }
}

void	info_joueur(t_core *core)
{
    int		i;
    int		z;
    int		c;

    i = 0;
    z = 0;
    c = 0;
    while (core->players[i])
    {
//        printf("ss %d\n", core->war_count);
        if (core->players[i]->nb == (core->war_count - \
		(core->war_count - core->players[i]->nb)))
        {
            attron(COLOR_PAIR(1 + c));
            mvprintw(3 + z, 198, "Player %d:", core->players[i]->nb);
            attroff(COLOR_PAIR(1 + c));
            mvprintw(4 + z, 198, core->players[i]->name);
            mvprintw(5 + z, 198, "Last live: %d", core->last_player);
        }
        i++;
        z = z + 10;
        c++;
    }
}

void	print_visu(t_core *core)
{
	info_joueur(core);
	print_arena_visu(core);
	mvprintw(50, 198, "Cycle : %d", core->cycle_after_start);
	mvprintw(52, 198, "Cycle to die : %d", core->cycle_to_die);
	mvprintw(53, 198, "Cycle delta : %d", CYCLE_DELTA);
	mvprintw(54, 198, "Lives : %d", core->live_count);
	mvprintw(55, 198, "Checks : %d / %d", core->game_check_count, MAX_CHECKS);
//	usleep(10000);
	refresh();
}

void		print_arena(t_core *core, int print_mode)
{
    int	i;
    int	j;

    i = 0;
    while (i < MEM_SIZE)
    {
        ft_printf("%.4p : ", i);
        j = 0;
        while (j < print_mode)
        {
            ft_printf("%.2x ", core->map[i + j]);
            j++;
        }
        ft_printf("\n");
        i += print_mode;
    }
}

void		show_fight_field(t_core *core)
{
    t_list	*pc;

    pc = core->pcs;
    if (core->dump == core->cycle_after_start)
    {
        print_arena(core, core->dump_print_mode);
        exit(0);
    }
    if (core->visual)
        print_visu(core);
}

// ******************************************** //


void		start_game(t_core *core)
{
	int		cycle_to_die;

	core->dump_print_mode = 32;
	core->cycle_to_die = CYCLE_TO_DIE;
	cycle_to_die = core->cycle_to_die;
	introduce(core);
	if (core->print_pc)
		ft_printf(" g_cycle | number | position | live_cycle |"\
		" op_cycle | carry | operation | registers\n");
	while (core->pcs)
	{
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
	}
}
