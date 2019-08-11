/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_i_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:35:06 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:24:43 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	9: zjmp {T_DIR} DSIZE 2
**
**	Эта та самая функция, на работу которой влияет значение флага carry.
**	Если оно равно 1, то функция обновляет значение PC на
**	адрес — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
**
**	То есть zjmp устанавливает куда должна переместиться каретка
**	для выполнения следующей операции.
**
**	Это позволяет нам перепрыгивать в памяти на нужную позицию,
**	а не выполнять всё по порядку.
**	Если значение carry равно нулю, перемещение не выполняется.
*/

static void	debug_info(t_list *carriage, t_arg *args, int old_pos)
{
	int		ofset;

	ft_printf("%10s > zjmp: ", CRG->owner->name);
	ofset = print_args(args, 1);
	while (--ofset)
		ft_putchar(' ');
	if (CRG->carry)
		ft_printf("| get jump: %d to %d\n", old_pos, adr((CURRENT + args[0].value) % IDX_MOD));
	else
		ft_printf("| no carry, current pos: %d\n", old_pos);
}

void	cw_zjmp(void *core, t_list *carriage)
{
	t_arg	args[1];
	int		old_pos;

	old_pos = CRG->position;

	init_args((t_arg *)args, carriage, 1);
	if (CRG->carry)
		CRG->position = adr((CURRENT + args[0].value) % IDX_MOD);

//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, (t_arg *)args, old_pos);
//##############################################

}
