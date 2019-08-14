/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:47:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/14 19:14:26 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	fill_map(t_core *core, int pc, int len, int player_id)
{
	int i;
	int value;

	i = pc;
	value = ((player_id - 1) % 4) + 1;
	while (i < len + pc)
	{
		core->visual.map[i].index = value + 1;
		i++;
	}
}

static void	init_attr(t_core *core)
{
	int	pc;
	int	id;

	pc = 0;
	id = 1;
	while (id <= core->war_count)
	{
		fill_map(core, pc, core->players[id - 1]->code_size, id);
		pc += MEM_SIZE / core->war_count;
		id++;
	}
}

void		init_colors(void)
{
    init_color(5, 250, 250, 250);
    init_pair(1, 1, COLOR_BLACK);
    init_pair(2, 4, COLOR_BLACK);
    init_pair(3, 6, COLOR_BLACK);
    init_pair(4, 3, COLOR_BLACK);
    init_pair(5, 0, COLOR_RED);
    init_pair(6, 0, COLOR_BLUE);
    init_pair(7, 0, COLOR_CYAN);
    init_pair(8, 0, COLOR_YELLOW);
    init_pair(9, 5, COLOR_BLACK);
    init_pair(10, 0, COLOR_MAGENTA);
}

void	init_window(t_core *core)
{
    initscr();
    getmaxyx(stdscr, core->visual.row, core->visual.col);
    if (core->visual.row <= 64 || core->visual.col <= 256)
        cw_clear_exit(core, "Make terminal more pls.", 1);
    start_color();
    init_colors();
}

void	init_visual(t_core *core)
{
	init_window(core);
	core->dump_print_mode = 32;
	init_attr(core);
}
