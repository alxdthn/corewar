/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_i_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:35:06 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/12 19:14:00 by nalexand         ###   ########.fr       */
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

static void	zjmp_print_process(t_core *core, t_list *carriage, t_arg *args)
{
	print_process_header(core, carriage);
	ft_printf("%d", args->value);
	if (CRG->carry == 1)
		ft_printf(" OK\n");
	else
		ft_printf(" FAILED\n");
}

void	cw_zjmp(void *core, t_list *carriage)
{
	t_arg	arg;
	int		old_pos;

	old_pos = CRG->position;

	init_args(&arg, carriage, 1);
	if (CRG->carry)
		CRG->position = adr(CURRENT + arg.value % IDX_MOD);
	else
		CRG->position = adr(CURRENT + 1 + arg.size);
	if (((t_core *)core)->out == 4)
		zjmp_print_process((t_core *)core, carriage, &arg);
}
