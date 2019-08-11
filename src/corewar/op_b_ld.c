/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_b_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:26:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 10:24:00 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	2: ld {T_DIR | T_IND}, {T_REG} DSIZE 4
**
**	Задача этой операции состоит в загрузке значения в регистр.
**	Но её поведение отличается в зависимости от типа первого аргумента:
**
**		Аргумент #1 — T_DIR
**		Число переданное в качестве аргумента будет воспринято «как есть».
**		Задачи операции:
**		- Записать полученное число в регистр, который был передан в качестве второго аргумента.
**
**		Аргумент #1 — T_IND
**		Число представляет собой адрес.
**		Задача операции:
**		- Определить адрес — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
**		- С полученного адреса необходимо считать 4 байта.
**		- Записать считанное число в регистр, который был передан в качестве второго параметра.
**
**		Если в регистр записали число 0, то устанавливаем значение carry в 1.
**		Если было записано не нулевое значение, то устанавливаем carry в 0.
*/

static void	debug_info(t_list *carriage, t_arg *args)
{
	int		ofset;

	ft_printf("%10s > ld:   ", CRG->owner->name);
	ofset = print_args((t_arg *)args, 2);
	while (--ofset)
		ft_putchar(' ');
	if (args[0].type == T_IND)
		ft_printf("| get %d from adr %d load to r%d\n",
		CRG->reg[args[1].value - 1],
		adr((CURRENT + args[0].value) % IDX_MOD), args[1].value);
	else
		ft_printf("| value from arg %d loaded to r%d\n",
		CRG->reg[args[1].value - 1], args[1].value);

}

void	cw_ld(void *core, t_list *carriage)
{
	t_arg	args[2];

	init_args((t_arg *)args, carriage, 2);
	if (args[0].type == T_IND)
		args[0].value = get_value_from_adr(carriage, args[0].value, IDX_MOD);
	CRG->reg[args[1].value - 1] = args[0].value;
	if (args[0].value == 0)
		CRG->carry = 1;
	else
		CRG->carry = 0;

//################## DEBUG: ####################
	if (DEBUG)
		debug_info(carriage, (t_arg *)args);
//##############################################

	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size);
}
