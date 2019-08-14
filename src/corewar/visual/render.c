/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:57:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/14 20:38:54 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				is_carry_here(t_core *core, int i)
{
	t_list	    *pc;
//    int			j;

//    j = 0;
	pc = core->pcs;
	while (pc)
	{
		if (PC->position == i)
			return (i);
//        j++;
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
//    if (id == -2)
//    {
//        attron(COLOR_PAIR(10));
//        mvprintw(y, x, "%02x", core->map[i]);
//        attroff(COLOR_PAIR(10));
//    }
	if (id != -1)
	{
		attron(COLOR_PAIR(GRAY_CURSOR));
		mvprintw(y, x, "%02x", core->map[i]);
		attroff(COLOR_PAIR(GRAY_CURSOR));
		//attron(COLOR_PAIR(core->visual.map[i].index));
		//mvprintw(y, x, "%02x", core->map[i]);
		//attroff(COLOR_PAIR(core->visual.map[i].index));
	}
	else
	{
		attron(COLOR_PAIR(GRAY));
		mvprintw(y, x, "%02x", core->map[i]);
		attroff(COLOR_PAIR(GRAY));
		//attron(COLOR_PAIR(core->visual.map[i].index));
		//mvprintw(y, x, "%02x", core->map[i]);
		//attroff(COLOR_PAIR(core->visual.map[i].index));
	}
}

void			render_arena(t_core *core)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 1;
	y = 1;
//    init_attr(core);
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

void	render_info(t_core *core)
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
//            mvprintw(5 + z, 198, "Last live: %d", core->last_player);
		}
		i++;
		z = z + 10;
		c++;
	}
}

void		render_window(t_core *core)
{
	render_info(core);
	render_arena(core);
	mvprintw(50, 198, "Cycle : %d", core->cycle_after_start);
	mvprintw(52, 198, "Cycle to die : %d", core->cycle_to_die);
	mvprintw(53, 198, "Cycle delta : %d", CYCLE_DELTA);
	mvprintw(54, 198, "Lives : %d", core->live_count);
	mvprintw(55, 198, "Checks : %d / %d", core->game_check_count, MAX_CHECKS);
	usleep(10000);
	refresh();
}

void		show_fight_field(t_core *core)
{
	render_window(core);
	if (core->visual.button == ESC)
		cw_clear_exit(core, NULL, 1);
	else if (core->visual.button == SPACE)
		while ((core->visual.button = getch()) != SPACE)
			if (core->visual.button == ESC)
				cw_clear_exit(core, NULL, 1);
	core->visual.button = getch();
}
