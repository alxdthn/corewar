//
// Created by Brenden Olson on 2019-08-14.
//

// ****************** Visual ****************** //

#include "corewar.h"

int				is_carry_here(t_core *core, int i)
{
    t_list	    *pc;
//    int			j;

//    j = 0;
    pc = core->pcs;
    while (pc)
    {
        if (PC->position == i)
            return (i);
//        j++;
        pc = pc->next;
    }
    return (-1);
}
//
#define MAX_COLOR_NUM 4
//
static void		print_arena_content(t_core *core, int i, int y, int x)
{
    int id;

    id = is_carry_here(core, i);
//    if (id == -2)
//    {
//        attron(COLOR_PAIR(10));
//        mvprintw(y, x, "%02x", core->map[i]);
//        attroff(COLOR_PAIR(10));
//    }
    if (id != -1)
    {
        attron(COLOR_PAIR(core->visual_str.map[i].index + 5));
        mvprintw(y, x, "%02x", core->map[i]);
        attroff(COLOR_PAIR(core->visual_str.map[i].index + 5));
    }
    else
    {
        attron(COLOR_PAIR(core->visual_str.map[i].index));
        mvprintw(y, x, "%02x", core->map[i]);
        attroff(COLOR_PAIR(core->visual_str.map[i].index));
    }
}

void			print_arena_visu(t_core *core)
{
    int		i;
    int		x;
    int		y;

    i = 0;
    x = 1;
    y = 1;
//    init_attr(core);
    while (i < MEM_SIZE)
    {
        print_arena_content(core, i, y, x);
        x = x + 2;
        mvprintw(y, x, " ");
        x++;
        if (i && (i + 1) % 64 == 0)
        {
            y++;
            x = 1;
        }
        i++;
    }
}

void	info_joueur(t_core *core)
{
    int		i;
    int		z;
    int		c;

    i = 0;
    z = 0;
    c = 0;
    while (core->players[i])
    {
//        printf("ss %d\n", core->war_count);
        if (core->players[i]->nb == (core->war_count - \
		(core->war_count - core->players[i]->nb)))
        {
            attron(COLOR_PAIR(1 + c));
            mvprintw(3 + z, 198, "Player %d:", core->players[i]->nb);
            attroff(COLOR_PAIR(1 + c));
            mvprintw(4 + z, 198, core->players[i]->name);
//            mvprintw(5 + z, 198, "Last live: %d", core->last_player);
        }
        i++;
        z = z + 10;
        c++;
    }
}

void	print_visu(t_core *core)
{
    info_joueur(core);
    print_arena_visu(core);
    mvprintw(50, 198, "Cycle : %d", core->cycle_after_start);
    mvprintw(52, 198, "Cycle to die : %d", core->cycle_to_die);
    mvprintw(53, 198, "Cycle delta : %d", CYCLE_DELTA);
    mvprintw(54, 198, "Lives : %d", core->live_count);
    mvprintw(55, 198, "Checks : %d / %d", core->game_check_count, MAX_CHECKS);
    usleep(10000);
    refresh();
}

void		print_arena(t_core *core, int print_mode)
{
    int	i;
    int	j;

    i = 0;
    while (i < MEM_SIZE)
    {
        ft_printf("%.4p : ", i);
        j = 0;
        while (j < print_mode)
        {
            ft_printf("%.2x ", core->map[i + j]);
            j++;
        }
        ft_printf("\n");
        i += print_mode;
    }
}

void        handle_buttons(t_core *core)
{
    if (core->visual_str.button == 27)
        cw_clear_exit(core, NULL, 1);
//    if (core->visual_str.button == ' ')
//        core
}

void		show_fight_field(t_core *core)
{
    core->visual_str.button = getch();
    printf("%d", core->visual_str.button);
        handle_buttons(core);
        if (core->dump == core->cycle_after_start) {
            print_arena(core, core->dump_print_mode);
            exit(0);
        }
        if (core->visual)
            print_visu(core);
}

static void	fill_map(t_core *core, int32_t pc, int32_t len, int32_t player_id)
{
    int32_t i;
    int32_t value;

    i = pc;
    value = ((player_id - 1) % 4) + 1;
    while (i < len + pc)
    {
        core->visual_str.map[i].index = value + 1;
        i++;
    }
}

static void	init_attr(t_core *core)
{
    int32_t	pc;
    int32_t	id;

    pc = 0;
    id = 1;
    while (id <= core->war_count)
    {
        fill_map(core, pc, core->players[id - 1]->code_size, id);
        pc += MEM_SIZE / core->war_count;
        id++;
    }
}

void       init_map_visual(t_core *core)
{
    init_attr(core);
    show_fight_field(core);
}