/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_i_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:35:06 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 02:52:06 by nalexand         ###   ########.fr       */
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

void	cw_zjmp(void *core, t_list *carriage)
{
	print_operation_info(CRG->op);
	ft_printf("current position: %d, ", CRG->position);
	if (CRG->carry)
		CRG->position
		= CRG->position
		+ ft_reverse_bytes(*((short *)(CRG->op + 1)), sizeof(short))
		% IDX_MOD;
	ft_printf("new position: %d, arg: %d\n", CRG->position, ft_reverse_bytes(*((short *)(CRG->op + 1)), sizeof(short)));	
	ft_printf("%{gre}s", "ZJMP IS DONE!\n");
}
