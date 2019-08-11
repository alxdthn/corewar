/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:12:39 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 11:14:47 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_lstdelnode(t_list **lst, t_list *node)
{
	t_list	*tmp;

	tmp = *lst;
	if (*lst == node)
	{
		*lst = node->next;
		free(node->content);
		free(node);
		return ;
	}
	while (tmp)
	{
		if (tmp->next == node)
		{
			tmp->next = node->next;
			free(node->content);
			free(node);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	game_check(t_core *core, int *cycle_to_die)
{
	t_list	*carriage;
	t_list	*tmp;

	if (core->live_count >= NBR_LIVE || core->live_check_count >= MAX_CHECKS)
	{
		core->cycle_to_die -= core->cycle_to_die_delta;
		core->live_check_count = 0;
	}	
	else
		core->live_check_count++;
	*cycle_to_die = core->cycle_to_die;
	carriage = core->carriages;
	while (carriage->next)
	{
		if (CRG->live == FALSE)
			ft_lstdelnode(&core->carriages, carriage);
		CRG->live = 0;
		carriage = carriage->next;
	}
}

static void	print_winner(t_core *core)
{
	t_list	*carriage;

	carriage = core->carriages;
	ft_printf("Contestant %d, %{gre}s, has won !\n",
	CRG->owner->nb, CRG->owner->name);
}

static void	introduce(t_core *core)
{
	int		i;

	i = 0;
	while (core->warriors[i])
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		core->warriors[i]->nb, core->warriors[i]->code_size,
		core->warriors[i]->name, core->warriors[i]->comment);
		i++;
	}
}

static void carriage_process(t_core *core)
{
	t_list	*carriage;
	int		ofset;

	carriage = core->carriages;
	while (carriage)
	{
		if ((ofset = validate_operation(core, carriage)))
			CRG->position = adr(CURRENT + ofset);
		else
		{
			if (CRG->cycle_for_op == 0)
				CRG->cycle_for_op = CRG->op_info->cycle;
			else
			{
				CRG->cycle_for_op--;
				if (CRG->cycle_for_op == 0)
					CRG->op_info->process(core, carriage);
			}
		}
		carriage = carriage->next;
	}
}

void 	start_game(t_core *core)
{
	int		cycle_to_die;

	core->cycle_to_die = CYCLE_TO_DIE;
	core->cycle_to_die_delta = CYCLE_DELTA;
	cycle_to_die = core->cycle_to_die;
	introduce(core);
	if (DEBUG)
		ft_printf("DEBUG MODE ACTIVATED!\n\n");
	while (core->carriages->next)
	{
		carriage_process(core);
		if (cycle_to_die-- <= 0)
			game_check(core, &cycle_to_die);
		core->cycle_after_start++;
	}
	print_winner(core);
}
