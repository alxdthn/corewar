/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 22:36:16 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 18:10:45 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_pcs(t_core *core)
{
	t_pc		new;
	t_list		*node;
	int			i;

	i = 0;
	ft_bzero(&new, sizeof(t_pc));
	while (core->players[i])
	{
		new.nb = i + 1;
		new.reg[0] = -core->players[i]->nb;
		new.owner = core->players[i];
		new.position = core->players[i++]->start_position;
		new.map = core->map;
		core->current_process_count++;
		core->global_process_count++;
		if (!(node = ft_lstnew(&new, sizeof(t_pc))))
			cw_clear_exit(core, MEM_ERROR, 2);
		ft_lstadd(&core->pcs, node);
	}
}
