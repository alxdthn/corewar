/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 14:28:25 by nalexand         ###   ########.fr       */
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

static int	validate_operation(const unsigned char *position, t_op **op)
{
	t_arg_type	argbyte;
	int			i;
	int			byteofset;
	char		arg;

	if (position[0] < 1 || position[0] > 16)
		return (ft_puterr(1, "NO OPERATION"));
	*op = &op_tab[position[0] - 1];
	print_operation_info(position);
	argbyte = position[1];
	i = 0;
	byteofset = (*op)->arg_type;
	while (i < (*op)->arg_count)
	{
		arg = get_arg_type(argbyte);
		byteofset += get_arg_ofset(arg, *op);
		if ((arg & (*op)->args[i]) != arg)
			return (ft_puterr(get_arg_size(*op, argbyte), "BAD_ARG"));
		if (arg == T_REG && (position[byteofset] < 0
		|| position[byteofset] > REG_NUMBER))
			return (ft_puterr(get_arg_size(*op, argbyte), "BAD_REG"));
		i++;
		argbyte <<= 2;
 	}
	return (0);
}

static void carriage_process(t_core *core, t_list *tmp)
{
	t_op	*cur_op;
	int		ofset;

	if ((ofset = validate_operation(core->map + CARRIAGE->position, &cur_op)))
		CARRIAGE->ofset += ofset;
	else
		ft_printf("ALL GOOD\n");
	print_carriage(tmp);
}

static void start_game(t_core *core)
{
	t_list	*tmp;

	tmp = core->carriages;
	while (tmp)
	{
		carriage_process(core, tmp);
		tmp = tmp->next;
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
	start_game(&core);

	ft_printf("\n\nCOREWAAAR!!!\n");
	cw_clear_exit(&core, NULL, 1);
	return (0);
}

	//print_memory(core.input->content, core.input->content_size);
	//print_warriros(&core);
	//print_map(core.map);
