/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:47:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/16 00:16:35 by nalexand         ###   ########.fr       */
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

#define BORDER 7

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
	init_pair(BORDER, 0, COLOR_GRAY);
}

static void	draw_border(t_core *core)
{
	int		y;

	wattron(core->visual.win, COLOR_PAIR(BORDER));
	wborder(core->visual.win, ' ', ' ',' ', ' ',' ', ' ', ' ',' ' );
	y = WIN_POSY;
	while (y < WIN_HEIGHT)
		mvwprintw(core->visual.win, y++, WIN_INFO_POSX, " ");
	wattroff(core->visual.win, COLOR_PAIR(BORDER));
}

static void	draw_players(t_core *core)
{
	int		i;
	int		x;

	i = 0;
	core->visual.y_ofset = 2;
	x = WIN_INFO_POSX + 4;
	while (core->players[i])
	{
		wattron(core->visual.win, COLOR_PAIR(GRAY + core->players[i]->id));
		mvwprintw(core->visual.win, core->visual.y_ofset++, x, "Player %d: %s",
		core->players[i]->nb, core->players[i]->name);
		mvwprintw(core->visual.win, core->visual.y_ofset++, x, "Comment: %s", core->players[i]->comment);
		mvwprintw(core->visual.win, core->visual.y_ofset++, x, "Size: %d", core->players[i]->code_size);
		wattroff(core->visual.win, COLOR_PAIR(GRAY + core->players[i++]->id));
		core->visual.y_ofset++;
	}
	core->visual.y_ofset++;
}

void	init_visual(t_core *core)
{
	core->dump_print_mode = 32;
	initscr();
	core->visual.win = newwin(WIN_HEIGHT, WIN_WIDTH, WIN_POSY, WIN_POSX);
	nodelay(core->visual.win, true);
	curs_set(false);
	noecho();
	use_default_colors();
	start_color();
	init_colors();
	core->visual.button = SPACE;
	init_attr(core);
	draw_border(core);
	draw_players(core);
}
