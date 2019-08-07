/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:29:22 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	set_exec_code(t_core *core)
{
	int		i;

	i = 0;
	while (core->warriors[i])
	{
		ft_memcpy(core->map + core->warriors[i]->start_position,
		core->warriors[i]->exec_code,
		core->warriors[i]->code_size);
		i++;
	}
}

static int	process(t_list *carriage)
{
	CRG->op_info->foo(carriage);	
	return (get_arg_size(CRG->op_info, CRG->op[ARG_BYTE]));
}

static void carriage_process(t_core *core, t_list *carriage)
{
	int		ofset;

	if ((ofset = validate_operation(carriage)))
		CRG->position += ofset;
	else
	{
		CRG->position += process(carriage);
		CRG->op = core->map + CRG->position;
		ft_printf("\033[32mALL GOOD\033[0m\n");
	}
}

static void start_game(t_core *core)
{
	t_list	*carriage;

	carriage = core->carriages;
	while (carriage)
	{
		CRG->op = core->map + CRG->position;
		while (*CRG->op)
			carriage_process(core, carriage);
		carriage = carriage->next;
	}
}

int			main(int ac, char **av)
{
	t_core	core;

	ft_bzero(&core, sizeof(t_core));
	read_input(&core, (const int)ac, (const char **)av);
	init_warriors(&core);
	init_carriages(&core);
	set_exec_code(&core);
	//start_game(&core);
	print_memory(core.input->content, core.input->content_size);

	ft_printf("\n\nCOREWAAAR!!!\n");
	cw_clear_exit(&core, NULL, 1);
	return (0);
}

	//print_warriros(&core);
	//print_map(core.map);
