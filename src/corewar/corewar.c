/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 04:18:04 by nalexand         ###   ########.fr       */
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

static void	fill_map(t_core *core, int32_t pc, int32_t len, int32_t player_id)
{
    int32_t i;
    int32_t value;

    i = pc;
    value = ((player_id - 1) % MAX_PLAYER_ID) + 1;
    while (i < len + pc)
    {
//        core.map[i].index = value;
        i++;
    }
}

static void	init_map(t_core *core)
{
    int32_t	pc;
    int32_t	id;

    pc = 0;
    id = 1;
    while (id <= core->war_count)
    {
        fill_map(core, pc, core->warriors[INDEX(id)]->code_size, id);
        pc += MEM_SIZE / core->war_count;
        id++;
    }
}

void		init_colors(void)
{
    init_color(COLOR_GRAY, 355, 355, 355);
    init_pair(GRAY, COLOR_GRAY, 0);
//    init_pair(GREEN, COLOR_GREEN, 0);
    init_pair(YELLOW, COLOR_YELLOW, 0);
//    init_pair(RED, COLOR_RED, 0);
//    init_pair(CYAN, COLOR_CYAN, 0);
//    init_pair(GRAY_CURSOR, COLOR_BLACK, COLOR_GRAY);
//    init_pair(GREEN_CURSOR, COLOR_BLACK, COLOR_GREEN);
    init_pair(YELLOW_CURSOR, COLOR_BLACK, COLOR_YELLOW);
//    init_pair(RED_CURSOR, COLOR_BLACK, COLOR_RED);
//    init_pair(CYAN_CURSOR, COLOR_BLACK, COLOR_CYAN);
//    init_pair(LIVE_GREEN, COLOR_WHITE, COLOR_GREEN);
    init_pair(LIVE_YELLOW, COLOR_WHITE, COLOR_YELLOW);
//    init_pair(LIVE_RED, COLOR_WHITE, COLOR_RED);
    init_pair(LIVE_CYAN, COLOR_WHITE, COLOR_CYAN);
}


void	draw_cursor(t_core *core, t_list *cursor)
{
    if (core->visual->map[cursor->content_size].index >= 0
        && core->visual->map[cursor->content_size].index <= MAX_PLAYER_ID)
        core->visual->map[cursor->content_size].index =
                INDEX_CURSOR(core->visual->map[cursor->content_size].index);
}

static void	init_cursors(t_core *core)
{
    t_list *carriage;

    carriage = core->carriages;

    while (carriage)
    {
        draw_cursor(core, carriage);
        printf("core = %d\n", CRG->position);
        carriage = carriage->next;
    }
}

void        configure_visual(t_core *core)
{
    initscr();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(false);
    cbreak();
    noecho();
    use_default_colors();
    start_color();
    init_colors();
    init_map(core);
    core->visual->arena = newwin(HEIGHT, WIDTH + 4, 1, 2);
    core->visual->win_info = newwin(HEIGHT, WIDTH / 4 + 10, 1, WIDTH + 6);
    core->visual->win_help = newwin(HEIGHT / 5, WIDTH, HEIGHT + 2, 2);
    init_cursors(core);
}

static void	draw_arena(t_core *core)
{
    static ssize_t	cycles = 0;
    int				i;
    int				j;
    int				attribute;

    i = 0;

    while (i < 64)
    {
        j = 0;
        wmove(core->visual->arena, i + 2, 5);
        while (j < 64)
        {
//            attribute = get_attribute(vm, &vm->vs->map[i * 64 + j], cycles);

//            attribute = core->map[i * 64 + j];
//            attribute = 1;
            wattron(core->visual->arena, 0);
//            wbkgd(core->visual->arena, COLOR_PAIR(YELLOW_CURSOR));
            wprintw(core->visual->arena, "%.2hhx", core->map[i * 64 + j]);
            wattroff(core->visual->arena, 0);
            waddch(core->visual->arena, ' ');
            j++;
        }
        wprintw(core->visual->arena, "\n");
        i++;
    }
//    cycles = vm->cycles;
}

static void	draw_border(WINDOW *win)
{
    wattron(win, COLOR_PAIR(YELLOW));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(YELLOW));
}

void		draw(t_core *core)
{
    werase(core->visual->arena);
    werase(core->visual->win_info);
    werase(core->visual->win_help);
    draw_arena(core);
//    draw_info(vm);
    draw_border(core->visual->arena);
//    wrefresh(vm->vs->win_info);
    wrefresh(core->visual->arena);
    wrefresh(core->visual->win_info);
    wrefresh(core->visual->win_help);
//    wrefresh(vm->vs->win_help);
}

void        make_visual(t_core *core)
{
    configure_visual(core);
    draw(core);
//    delwin(core->visual->arena);
//    endwin();
}

int			main(int ac, char **av)
{
	t_core	core;

	ft_bzero(&core, sizeof(t_core));
	read_input(&core, (const int)ac, (const char **)av);
	init_warriors(&core);
	init_carriages(&core);
	set_exec_code(&core);
//	print_map(&core, 1);
	start_game(&core);
//	if (core.visual)
//    {
	    make_visual(&core);
//    }

	//print_carriage(core.carriages);
	//print_warriros(&core);

	//print_memory(core.input->content, core.input->content_size);

	cw_clear_exit(&core, NULL, 1);
	return (0);
}

	//print_warriros(&core);
	//print_map(core.map);
