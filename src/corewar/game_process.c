/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:12:39 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/08 19:43:04 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	set_carriage_operations(t_core *core)
{
	t_list	*carriage;

	carriage = core->carriages;
	while (carriage)
	{
		CRG->op = core->map + CRG->position;
		carriage = carriage->next;
	}
}

static void	game_check(t_core *core)
{
	t_list	*carriage;
	t_list	*tmp;

	carriage = core->carriages;
	while (carriage->next)
	{
		if (CRG_NEXT->live == 0)
		{
			tmp = carriage->next->next;
			ft_lstdelone(&carriage->next, ft_lstclear);
			carriage->next = tmp;
		}
		carriage = carriage->next;
	}
}

static void	print_winner(t_core *core)
{

}

void 	start_game(t_core *core)
{
	set_carriage_operations(core);
	while (core->carriages->next)
	{
		game_check(core);
		core->cycle_after_start++;
	}
	print_winner(core);
}
