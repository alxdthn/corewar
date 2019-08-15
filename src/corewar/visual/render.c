/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:57:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/16 00:16:48 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define MAX_COLOR_NUM 4

static void		print_arena_content(t_core *core, int i, int y, int x)
{
	t_attr	*attr;
	int		currnet_attr;

	attr = &core->visual.attrs[i];
	if (attr->live_player_id)
		currnet_attr = COLOR_PAIR(attr->live_player_id) | A_BOLD;
	else
	{
		if (attr->light)
		{
			currnet_attr = COLOR_PAIR(attr->index + attr->pc_here) | A_BOLD;
			attr->light--;
		}
		else
			currnet_attr = COLOR_PAIR(attr->index + attr->pc_here);
	}
	wattron(core->visual.win, currnet_attr);
	mvwprintw(core->visual.win, y, x, "%02x", core->map[i]);
	wattroff(core->visual.win, currnet_attr);
}

void			render_arena(t_core *core)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 4;
	y = 2;
	while (i < MEM_SIZE)
	{
		print_arena_content(core, i, y, x);
		x += 3;
//		mvwprintw(core->visual.win, y, x++, " ");
		if (i && (i + 1) % 64 == 0)
		{
			y++;
			x = 4;
		}
		i++;
	}
}

void	render_info(t_core *core)
{
	mvwprintw(core->visual.win, core->visual.y_ofset + 1, WIN_INFO_POSX + 4, "Cycle : %d", core->cycle_after_start);
	mvwprintw(core->visual.win, core->visual.y_ofset + 2, WIN_INFO_POSX + 4, "Cycle to die : %-4d", core->cycle_to_die);
	mvwprintw(core->visual.win, core->visual.y_ofset + 3, WIN_INFO_POSX + 4, "Cycle delta : %d", CYCLE_DELTA);
	mvwprintw(core->visual.win, core->visual.y_ofset + 4, WIN_INFO_POSX + 4, "Lives : %-10d", core->live_count);
	mvwprintw(core->visual.win, core->visual.y_ofset + 5, WIN_INFO_POSX + 4, "Checks : %-2d / %-2d", core->game_check_count, MAX_CHECKS);
}

void		render_window(t_core *core)
{
	render_arena(core);
	render_info(core);
//	usleep(10000);
}

#define S_BTN 's'

static void	handle_buttons(t_core *core)
{
	core->visual.button = wgetch(core->visual.win);
	if (core->visual.button == ESC)
		cw_clear_exit(core, NULL, 1);
	else if (core->visual.button == SPACE)
		core->visual.running = !core->visual.running;
	else if (core->visual.button == S_BTN)
		core->visual.running = 1;
}

void		show_fight_field(t_core *core)
{
	render_window(core);
	wrefresh(core->visual.win);
	if (core->visual.button == S_BTN)
		core->visual.running = 0;
	if (!core->visual.running)
		while (!core->visual.running)
			handle_buttons(core);
	else
		handle_buttons(core);
}
