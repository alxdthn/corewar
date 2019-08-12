//
// Created by Brenden Olson on 2019-08-09.
//

#include "corewar.h"

t_visual    *init_visual(void)
{
    t_visual *visual;

    if (!(visual = (t_visual *)ft_memalloc(sizeof(t_visual))))
        exit(EXIT_FAILURE);
    visual->arena = NULL;

    return (visual);
}

void		get_visual(int *ac, t_core *core, int *i)
{
    core->visual = init_visual();
//    (*ac)--;
//    (*i)++;
}