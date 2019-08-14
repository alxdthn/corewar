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


// ****************** Visual ****************** //

void	init_colors(void)
{
    init_color(5, 250, 250, 250);
    init_pair(1, 1, COLOR_BLACK);
    init_pair(2, 4, COLOR_BLACK);
    init_pair(3, 6, COLOR_BLACK);
    init_pair(4, 3, COLOR_BLACK);
    init_pair(5, 0, COLOR_RED);
    init_pair(6, 0, COLOR_BLUE);
    init_pair(7, 0, COLOR_CYAN);
    init_pair(8, 0, COLOR_YELLOW);
    init_pair(9, 5, COLOR_BLACK);
    init_pair(10, 0, COLOR_MAGENTA);
}

t_visual	init_visual()
{
    t_visual visual;

    initscr();
    getmaxyx(stdscr, visual.row, visual.col);
    if (visual.row <= 64 || visual.col <= 256)
    {
        clear();
        endwin();
        ft_printf("Make terminal more pls.\n");
        exit(0);
    }
    start_color();
    init_colors();
    return (visual);
}

static void	get_flag(t_core *core, int *flag, int value, int arg_ofset)
{
    core->arg_ofset += arg_ofset;
    if (core->visual == 'v')
        init_visual();
    *flag = value;
}

// ******************************************** //

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
        {
		    core->visual = 'v';
            get_flag(core, &core->out, ft_atoi(av[++i]), 2);
        }
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
