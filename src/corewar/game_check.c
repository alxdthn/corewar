/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:03:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/15 16:39:41 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	remove_pcs(t_core *core)
{
	t_list	*pc;
	t_list	*tmp;

	pc = core->pcs;
	while (pc)
	{
		if (PC->cycle >= core->cycle_to_die || core->cycle_to_die <= 0)
		{
			tmp = pc->next;
			if (core->out == 8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				PC->nb, PC->cycle, core->cycle_to_die);
			ft_lstdelnode(&core->pcs, pc);
			core->current_process_count--;
			pc = tmp;
		}
		else
			pc = pc->next;
	}
}

static void	clear_lives(t_core *core)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
		core->visual.attrs[i++].live_player_id = 0;
}

void		game_check(t_core *core, int *cycle_to_die)
{
	remove_pcs(core);
	if (core->visu_mod)
		clear_lives(core);
	core->game_check_count++;
	if (core->live_count >= NBR_LIVE || core->game_check_count >= MAX_CHECKS)
	{
		core->cycle_to_die -= CYCLE_DELTA;
		core->game_check_count = 0;
		if (core->out == 2)
			ft_printf("Cycle to die is now %d\n", core->cycle_to_die);
	}
	*cycle_to_die = core->cycle_to_die;
	core->live_count = 0;
}
