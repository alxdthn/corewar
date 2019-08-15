/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:47:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/15 16:23:29 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	fill_map(t_core *core, int pc, int len, int player_id)
{
	int		i;

	i = pc;
	while (i < len + pc)
		core->visual.attrs[i++].index = GRAY + player_id;
}

static void	init_attr(t_core *core)
{
	int		pos;
	int		i;

	i = 0;
	while (i < MEM_SIZE)
		core->visual.attrs[i++].index = GRAY;
	pos = 0;
	i = 1;
	while (i <= core->war_count)
	{
		fill_map(core, pos, core->players[i - 1]->code_size, i);
		core->visual.attrs[pos].pc_here = 5;
		pos += MEM_SIZE / core->war_count;
		i++;
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
	init_pair(LIVE_GREEN, COLOR_GREEN, 0);
	init_pair(LIVE_YELLOW, COLOR_YELLOW, 0);
	init_pair(LIVE_RED, COLOR_RED, 0);
	init_pair(LIVE_CYAN, COLOR_CYAN, 0);
}

void	init_visual(t_core *core)
{
	core->dump_print_mode = 32;
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	use_default_colors();
	start_color();
	init_colors();
	getmaxyx(stdscr, core->visual.row, core->visual.col);
	if (core->visual.row <= 64 || core->visual.col <= 256)
		cw_clear_exit(core, "Make terminal more pls.", 1);
	core->visual.button = SPACE;
	init_attr(core);
}
/*
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	use_default_colors();
	start_color();
	init_colors();
	init_map(vm);
	vm->vs->win_arena = newwin(HEIGHT, WIDTH + 4, 1, 2);
	vm->vs->win_info = newwin(HEIGHT, WIDTH / 4 + 10, 1, WIDTH + 6);
	vm->vs->win_help = newwin(HEIGHT / 5, WIDTH, HEIGHT + 2, 2);
	init_cursors(vm);
*/