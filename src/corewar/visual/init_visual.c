/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:47:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/14 20:24:50 by nalexand         ###   ########.fr       */
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
	init_color(COLOR_GRAY, 355, 355, 355);
	init_pair(GRAY, COLOR_GRAY, 0);
	init_pair(GREEN, COLOR_GREEN, 0);
	init_pair(YELLOW, COLOR_YELLOW, 0);
	init_pair(REDD, COLOR_RED, 0);
	init_pair(CYAN, COLOR_CYAN, 0);
	init_pair(GRAY_CURSOR, COLOR_BLACK, COLOR_GRAY);
	init_pair(GREEN_CURSOR, COLOR_BLACK, COLOR_GREEN);
	init_pair(YELLOW_CURSOR, COLOR_BLACK, COLOR_YELLOW);
	init_pair(RED_CURSOR, COLOR_BLACK, COLOR_RED);
	init_pair(CYAN_CURSOR, COLOR_BLACK, COLOR_CYAN);
	init_pair(LIVE_GREEN, COLOR_WHITE, COLOR_GREEN);
	init_pair(LIVE_YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair(LIVE_RED, COLOR_WHITE, COLOR_RED);
	init_pair(LIVE_CYAN, COLOR_WHITE, COLOR_CYAN);
}

void	init_visual(t_core *core)
{
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	use_default_colors();
    getmaxyx(stdscr, core->visual.row, core->visual.col);
    if (core->visual.row <= 64 || core->visual.col <= 256)
        cw_clear_exit(core, "Make terminal more pls.", 1);
	init_colors();
    start_color();
	core->dump_print_mode = 32;
	core->visual.button = SPACE;
	init_attr(core);
}
