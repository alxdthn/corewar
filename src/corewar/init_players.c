/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:35:29 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/14 22:18:37 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	set_start_position(t_core *core)
{
	int			start;
	int			i;

	i = 0;
	start = 0;
	while (core->players[i])
	{
		core->players[i++]->start_position = start;
		start += MEM_SIZE / core->war_count;
	}
}

static void	check_new_numbers(t_core *core, int ac, char **av)
{
	int		i;
	int		j;

	i = core->arg_ofset;
	j = core->war_count - 1;
	while (i < ac && core->players[j])
	{
		if (ft_strequ("-n", av[i]) && i + 1 < ac && ft_isint(av[i + 1]))
		{
			core->players[j]->nb = ft_atoi(av[++i]);
			j--;
		}
		i++;
	}
}

void		init_players(t_core *core, int ac, char **av)
{
	t_list		*input;
	t_player	*new;
	int			nb;
	int			i;

	input = core->input;
	nb = core->war_count;
	i = nb;
	while (input)
	{
		if (!(new = (t_player *)malloc(sizeof(t_player))))
			cw_clear_exit(core, MEM_ERROR, 2);
		new->nb = nb;
		new->id = nb--;
		new->name = STR(input) + NAME_OFSET;
		new->comment = STR(input) + COMMENT_OFSET;
		new->code_size = GET_VAL(input->content + CODE_SIZE_OFSET, int);
		new->exec_code = STR(input) + EXEC_CODE_OFSET;
		core->players[--i] = new;
		input = input->next;
	}
	set_start_position(core);
	check_new_numbers(core, ac, av);
}
