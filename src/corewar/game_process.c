/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:12:39 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 20:07:35 by nalexand         ###   ########.fr       */
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

static void	print_winner(t_core *core)
{
	t_list	*carriage;

	carriage = core->carriages;
	ft_printf("Contestant %d, \"%s\", has won !\n",
	CRG->owner->nb, CRG->owner->name);
}

static void	introduce(t_core *core)
{
	int		i;

	i = 0;
	if (core->out != 8)
		ft_printf("Introducing contestants...\n");
	while (core->warriors[i])
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		core->warriors[i]->nb, core->warriors[i]->code_size,
		core->warriors[i]->name, core->warriors[i]->comment);
		i++;
	}
}


void		validate_op_code(t_list *carriage)
{
	CRG->op = BYTE(CURRENT);
	if (CRG->op > 0 && CRG->op < 17)
	{
		CRG->op_info = &op_tab[CRG->op - 1];
		CRG->cycle_for_op = CRG->op_info->cycle;
	}
	else
		CRG->position = adr(CURRENT + 1);
}

static void	game_check(t_core *core, int *cycle_to_die)
{
	t_list	*carriage;
	t_list	*tmp;

//	ft_printf("%d\n", core->process_count);
	core->game_check_count++;
	if (core->live_count >= NBR_LIVE || core->game_check_count >= MAX_CHECKS)
	{
		core->cycle_to_die -= core->cycle_to_die_delta;
		core->game_check_count = 0;
		if (core->out == 2)
			ft_printf("Cycle to die is now %d\n", core->cycle_to_die);
	}
	*cycle_to_die = core->cycle_to_die;
	carriage = core->carriages;
	while (carriage)
	{
		if (CRG->cycle_after_live >= core->cycle_to_die || core->cycle_to_die <= 0)
		{
			if (core->out == 8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", CRG->nb, CRG->cycle_after_live, *cycle_to_die);
			if (core->current_process_count == 1)
				print_winner(core);
			ft_lstdelnode(&core->carriages, carriage);
			core->current_process_count--;
		}
		CRG->cycle_after_live = 0;
		carriage = carriage->next;
	}
	core->live_count = 0;
}

static void carriage_process(t_core *core)
{
	t_list	*carriage;
	int		ofset;

	carriage = core->carriages;
	while (carriage)
	{
		if (CRG->cycle_after_live)
			CRG->cycle_after_live++;
		if (!CRG->op)
			validate_op_code(carriage);
		if (CRG->op_info)
		{
			CRG->cycle_for_op--;
			if (CRG->cycle_for_op == 0)
			{
				if ((ofset = validate_operation(core, carriage)))
					CRG->position = adr(CURRENT + ofset);
				else
				{
					CRG->op_info->process(core, carriage);
					CRG->op = 0;
					CRG->op_info = NULL;
				}
			}
		}
//		if (ofset == 1)
//			cw_clear_exit(core, NULL, 1);
		carriage = carriage->next;
	}
}

void	print_dump(t_core *core)
{
	print_map(core, 1);
	cw_clear_exit(core, NULL, 1);
}

void 	start_game(t_core *core)
{
	int		cycle_to_die;
	int		test;

	core->cycle_to_die = CYCLE_TO_DIE;
	core->cycle_to_die_delta = CYCLE_DELTA;
	cycle_to_die = core->cycle_to_die;
	introduce(core);
	while (core->carriages)
	{
		if (core->cycle_after_start == core->dump)
			print_dump(core);
		carriage_process(core);
		if (cycle_to_die <= 0)
			game_check(core, &cycle_to_die);
		core->cycle_after_start++;
		cycle_to_die--;
		if (core->out == 2)
			ft_printf("It is now cycle %d\n", core->cycle_after_start);
	}
}
