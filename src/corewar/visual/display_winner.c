/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_winner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 22:05:54 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/15 23:41:22 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			display_winner(t_core *core)
{
	t_player	*winner;

	if (core->last_player)
		winner = core->last_player;
	else
		winner = core->players[0];
	wattron(core->visual.win, COLOR_PAIR(winner->id + 1));
	mvwprintw(core->visual.win, 40, 198, "!!!!!!!!! %s win !!!!!!!!\n", winner->name);
	refresh();
	while (core->visual.button != ESC)
		core->visual.button = wgetch(core->visual.win);
	cw_clear_exit(core, NULL, 0);
}
