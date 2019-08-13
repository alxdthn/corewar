/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/13 22:04:27 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	set_exec_code(t_core *core)
{
	int		i;

	i = 0;
	while (core->players[i])
	{
		ft_memcpy(core->map + core->players[i]->start_position,
		core->players[i]->exec_code,
		core->players[i]->code_size);
		i++;
	}
}

void		parce_flags(t_core *core, int ac, char **av)
{
	int		i;

	i = 1;
	core->dump = -1;
	if (ac > 2)
	{
		if (ft_strequ("-d", av[1]))
			if (ac > 3)
				core->dump = ft_atoi(av[2]);
		if (ft_strequ("-v", av[1]))
			if (ac > 3)
				core->out = ft_atoi(av[2]);
		if (ft_strequ("-c", av[1]))
			if (ac > 3)
				core->print_pc = ft_atoi(av[2]);
	}
	if (core->out || core->dump >= 0 || core->print_pc)
		core->arg_ofset = 2;
}

int			main(int ac, char **av)
{
	t_core	core;

	ft_bzero(&core, sizeof(t_core));
	parce_flags(&core, ac, av);
	read_input(&core, (const int)ac, (const char **)av);
	init_players(&core);
	init_processes(&core);
	set_exec_code(&core);
	start_game(&core);
	cw_clear_exit(&core, NULL, 1);
	return (0);
}
