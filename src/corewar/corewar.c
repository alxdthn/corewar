/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 20:37:48 by skrystin         ###   ########.fr       */
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

static int	validate_operation(char *position, t_op **op)
{
	t_arg_type	argbyte;
	int			i;
	int			arg_ofset;
	int			byte_ofset;
	char		arg_type;
	char		arg_code;

	if (position[0] < 1 || position[0] > 16)
		return (ft_puterr(1, "NO OPERATION"));
	*op = &op_tab[position[0] - 1];
	print_operation_info(position);
	argbyte = position[1];
	byte_ofset = 1 + (((*op)->arg_count == 1) ? 0 : 1);
	i = 0;
	while (i < (*op)->arg_count)
	{
		arg_type = get_arg_type(argbyte);
		arg_code = get_arg_code(arg_type);
		arg_ofset = get_arg_ofset(arg_type, *op);
		if ((arg_code & (*op)->args[i]) != arg_code)
			return (ft_puterr(get_arg_size(*op, argbyte), "\033[31mBAD_ARG\033[0m"));
		if (arg_type == T_REG && (position[byte_ofset] < 0
		|| position[byte_ofset] > REG_NUMBER))
			return (ft_puterr(get_arg_size(*op, argbyte), "BAD_REG"));
		i++;
		argbyte <<= 2;
		byte_ofset += arg_ofset;
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
		ft_printf("\033[32mALL GOOD\033[0m\n");
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
	//start_game(&core);
	print_memory(core.input->content, core.input->content_size);

	ft_printf("\n\nCOREWAAAR!!!\n");
	cw_clear_exit(&core, NULL, 1);
	return (0);
}

	//print_warriros(&core);
	//print_map(core.map);
