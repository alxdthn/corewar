/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:57:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/15 16:20:54 by nalexand         ###   ########.fr       */
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
	attron(currnet_attr);
				// wattron(core->visual.win_arena, 3);

			// wprintw(core->visual.win_arena, "%.2x", core->map[i]);
	mvprintw(y, x, "%02x", core->map[i]);
	attroff(currnet_attr);
}

void			render_arena(t_core *core)
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
		waddch(core->visual.win_arena, ' ');

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
		if (core->players[i]->nb == (core->war_count
		- (core->war_count - core->players[i]->nb)))
		{
			attron(COLOR_PAIR(GRAY + core->players[i]->id));
			mvprintw(3 + z, 198, "Player %d:", core->players[i]->nb);
			attroff(COLOR_PAIR(GRAY + core->players[i]->id));
			mvprintw(4 + z, 198, core->players[i]->name);
		}
		i++;
		z = z + 10;
		c++;
	}
}

//////////////////////////


static void	draw_arena(t_core *core)
{
	static ssize_t	cycles = 0;
	int				i;
	int				j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		// wmove(core->visual.win_arena, i + 2, 5);
		while (j < 64)
		{
			// attribute = get_attribute(vm, &vm->vs->map[i * 64 + j], cycles);
			wattron(core->visual.win_arena, 3);
			wprintw(core->visual.win_arena, "%.2x", core->map[i * 64 + j]);
			// wattroff(core->visual.win_arena, attribute);
			waddch(core->visual.win_arena, ' ');
			j++;
		}
		wprintw(core->visual.win_arena, "\n");
		i++;
	}
	cycles = core->cycle_after_start;
}



///////////////////////

void		render_window(t_core *core)
{ 
	render_arena(core);
	// draw_arena(core);
	render_info(core);
	mvprintw(50, 198, "Cycle : %d", core->cycle_after_start);
	mvprintw(52, 198, "Cycle to die : %d", core->cycle_to_die);
	mvprintw(53, 198, "Cycle delta : %d", CYCLE_DELTA);
	mvprintw(54, 198, "Lives : %d", core->live_count);
	mvprintw(55, 198, "Checks : %d / %d", core->game_check_count, MAX_CHECKS);
//	usleep(10000);
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
