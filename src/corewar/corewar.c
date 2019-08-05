/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/05 22:28:12 by nalexand         ###   ########.fr       */
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

void	print_operation_info(char *position)
{
	t_op			*op;
	int				i;
	unsigned char	arg_byte;
	int				ofset;
	int				byte_ofset;

	op = &op_tab[position[0] - 1];
	ft_printf("__name__|________args_________|_carry_|__description_\n");
	ft_printf("%-8s|", op->op_name);
	ofset = 0;
	if (op->arg_count == 1 && op->args[0] == T_DIR)
		ofset += ft_printf("T_DIR{%d} ", position[4]);
	else
	{
		arg_byte = position[1];
		byte_ofset = 1;
		while (arg_byte)
		{
			if ((arg_byte & (T_REG << 6)) == (T_REG << 6))
				ofset += ft_printf("r%d, ", position[(byte_ofset += 1)]);
			else if ((arg_byte & (T_DIR << 6)) == (T_DIR << 6))
				ofset += ft_printf("%%%d, ", position[(byte_ofset += op->t_dir_size)]);
			else if ((arg_byte & (T_IND << 6)) == (T_IND << 6))
				ofset += ft_printf("%d, ", position[(byte_ofset += 2)]);
			arg_byte <<= 2;
		}
	}
	ofset = 21 - ofset;
	while (--ofset >= 0)
		ft_putchar(' ');
	if (op->carry)
		ft_printf("|  yes  ");
	else
		ft_printf("|  no   ");
	ft_printf("|%s\n", op->description);
}

static void carriage_process(t_core *core, t_list *tmp)
{
	CARRIAGE->op = core->map[CARRIAGE->position];
}

static void start_game(t_core *core)
{
	t_list	*tmp;

	tmp = core->carriages;
	while (tmp)
	{
		carriage_process(core, tmp);
		ft_printf("CARRIAGE INFO:\n");
		print_carriage(tmp);
		ft_printf("OPERATION INFO:\n");
		print_operation_info((char *)core->map + CARRIAGE->position);
		tmp = tmp->next;
	}
}

int			main(int ac, char **av)
{
	t_core	core;

	ft_bzero(&core, sizeof(t_core));
	read_input(&core, (const int)ac, (const char **)av);
	init_warriors(&core);
	set_exec_code(&core);
	init_carriages(&core);
	print_warriros(&core);
	start_game(&core);

//	print_map(core.map);

	ft_printf("\n\nCOREWAAAR!!!\n");
	cw_clear_exit(&core, NULL, 1);
	return (0);
}
