/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:03:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/13 17:04:59 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_winner(t_core *core)
{
	int		i;

	i = 0;
	while (core->warriors[i])
	{
		if (core->warriors[i]->live == TRUE)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n",
			core->warriors[i]->nb, core->warriors[i]->name);
			cw_clear_exit(core, NULL, 1);
		}
		i++;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n",
	core->warriors[0]->nb, core->warriors[0]->name);
	cw_clear_exit(core, NULL, 1);
}

static void	remove_pcs(t_core *core)
{
	t_list	*pc;
	t_list	*tmp;
	int		i;

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
	if (core->current_process_count == 0)
		print_winner(core);
	i = 0;
	while (core->warriors[i])
		core->warriors[i++]->live = FALSE;
}

void		game_check(t_core *core, int *cycle_to_die)
{
	remove_pcs(core);
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
