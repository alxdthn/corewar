/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/06 22:17:21 by nalexand         ###   ########.fr       */
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

static void	init_carriages(t_core *core)
{
	t_carriage	new;
	t_list		*node;
	int			i;

	i = 0;
	ft_bzero(&new, sizeof(t_carriage));
	while (core->warriors[i])
	{
		new.nb = i + 1;
		new.reg[0] = -core->warriors[i]->nb;
		new.position = core->warriors[i++]->start_position;
		if (!(node = ft_lstnew(&new, sizeof(t_carriage))))
			cw_clear_exit(core, MEM_ERROR, 2);
		ft_lstadd(&core->carriages, node);
	}
}

static int	get_arg_type(char byte)
{
	char	mask;

	mask = (byte & 0xC0) >> 6;
	if (mask == DIR_CODE)
		return (T_DIR);
	else if (mask == IND_CODE)
		return (T_IND);
	else if (mask == REG_CODE)
		return (T_REG);
	return (0);
}

static int	validate_operation(const unsigned char *position, t_op **cur)
{
	t_arg_type	argbyte;
	int			i;
	int			byteofset;
	char		mask;

	if (!position[0] || position[0] > 16)
		return (ft_puterr(1, "NO OPERATION"));
	*cur = &op_tab[position[0] - 1];
	print_operation_info(position);
	argbyte = position[1];
	i = 0;
	byteofset = 0;
	while (i < (*cur)->arg_count)
	{
		mask = get_arg_type(argbyte);
		if ((mask & (*cur)->args[i]) != mask)
			return (ft_puterr(1, "BAD_ARG"));
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
	{
		ft_printf("ERROR\n");
		CARRIAGE->ofset += ofset;
	}
	CARRIAGE->op = cur_op->op_code;
	//else
		//print_carriage(tmp);
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

	//print_warriros(&core);
	//print_map(core.map);
	//print_memory(core.input->content, core.input->content_size);