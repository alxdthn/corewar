/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 18:45:18 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/08 23:03:08 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
/*
**	Функции для дебага, исходя из названия думаю понятно что они печатают
*/

static void	print_carriage_on_map(t_core *core, int i)
{
	t_list	*carriage;
	char	*color;

	carriage = core->carriages;
	while (carriage)
	{
		if (i == CRG->position)
		{
			if (CRG->owner->nb == 1)
				color = GRE;
			else if (CRG->owner->nb == 2)
				color = YEL;
			ft_printf("%s%.2x%s", color, core->map[i], EOC);
			return ;
		}
		carriage = carriage->next;
	}
	ft_printf("%.2x",  core->map[i]);
}

void	print_map(t_core *core)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	line_size;
	unsigned int	bar;

	line_size = MEM_SIZE / 64;
	i = 0;
	j = line_size;
	bar = 64;
	while (i < MEM_SIZE / bar)
	{
		print_carriage_on_map(core, i++);
		if (--j)
			ft_putchar(' ');
		else
			ft_putchar('\n');
		if (!j)
			j = line_size;
	}
}

void	print_input(t_list *tmp)
{
	while (tmp)
	{
		ft_printf("%s", STR(tmp));
		tmp = tmp->next;
	}
}

void	print_warriros(t_core *core)
{
	int		i;

	i = 0;

	while (core->warriors[i])
	{
		ft_printf("number: %d\n", core->warriors[i]->nb);
		ft_printf("name: %s\n", core->warriors[i]->name);
		ft_printf("comment: %s\n", core->warriors[i]->comment);
		ft_printf("start_position: %d\n", core->warriors[i]->start_position);
		ft_printf("code_size: %d\n", core->warriors[i]->code_size);
		print_memory(core->warriors[i]->exec_code, core->warriors[i]->code_size);
		ft_printf("--------------------------------------\n");
		++i;
	}
}

void	print_carriage(t_list *carriage)
{
	int		i;

	ft_printf("CARRIAGE INFO:\n");
	ft_printf("number: %d\nposition: %d\ncycle_for_op: %d\ncycle: %d\n"\
	"carry: %d\noperation %s\nofset: %d\nregisters:\n",
	CRG->nb, CRG->position, CRG->cycle_for_op, CRG->cycle,
	CRG->carry, CRG->op_info->op_name, CRG->ofset);
	i = 0;
	while (i < REG_NUMBER)
		ft_printf("%.*x ", REG_SIZE, CRG->reg[i++]);
	ft_putchar('\n');
	ft_putstr("--------------------------------\n");
}
