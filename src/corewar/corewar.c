/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/13 23:10:25 by nalexand         ###   ########.fr       */
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

static void	get_flag(t_core *core, int *flag, int value, int arg_ofset)
{
	core->arg_ofset += arg_ofset;
	*flag = value;
}

void		parce_flags(t_core *core, int ac, char **av)
{
	int		i;

	i = 1;
	core->d = -1;
	core->dump = -1;
	while (i < ac)
	{
		if (ft_strequ("-d", av[i]) && i + 1 < ac)
			get_flag(core, &core->d, ft_atoi(av[++i]), 2);
		if (ft_strequ("-dump", av[i]) && i + 1 < ac)
			get_flag(core, &core->dump, ft_atoi(av[++i]), 2);
		else if (ft_strequ("-v", av[i]) && i + 1 < ac)
			get_flag(core, &core->out, ft_atoi(av[++i]), 2);
		else if (ft_strequ("-c", av[i]) && i + 1 < ac)
			get_flag(core, &core->print_pc, ft_atoi(av[++i]), 2);
		else if (ft_strequ("-a", av[i]) && i + 1 < ac)
			get_flag(core, &core->print_aff, 1, 1);
		i++;
	}
}

int			main(int ac, char **av)
{
	t_core	core;

	ft_bzero(&core, sizeof(t_core));
	parce_flags(&core, ac, av);
	read_input(&core, ac, av);
	init_players(&core, ac, av);
	init_processes(&core);
	set_exec_code(&core);
	start_game(&core);
	cw_clear_exit(&core, NULL, 1);
	return (0);
}
