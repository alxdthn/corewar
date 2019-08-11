/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_j_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:35:52 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 20:23:55 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*	
**	10: ldi {T_REG | T_DIR | T_IND}, {T_REG | T_DIR}, {T_REG} DSIZE 2
**
**	Данная операция записывает значение в регистр, 
**	который был ей передан как третий параметр.
**	Значением, которая она записывает, являются 4 байта.
**	Эти 4 байта она считывает по адресу,
**	который формируется по следующему принципу:
**	текущая позиция + (<ЗНАЧЕНИЕ_ПЕРВОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА>) % IDX_MOD.
**
**	Поскольку операция может принимать разные типы
**	первого и второго аргументов,
**	рассмотрим способ получения значения для каждого типа:
**
**		Аргумент #1 / Аргумент #2 — T_REG
**		- Значение содержится в регистре, который был передан в качестве параметра.
**
**		Аргумент #1 / Аргумент #2 — T_DIR
**		- В данном случае у нас аргумент уже содержит свое значение.
**
**		Аргумент #1 — T_IND
**		- Чтобы получить значение этого аргумента,
**		нужно считать 4 байта по адресу — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
*/

static void	ldi_print_process(t_list *carriage, t_arg *args, int a, int b)
{
	int		i;

	ft_printf("P%5d | %s ", CRG->nb, CRG->op_info->op_name);
	i = 0;
	while (i < 3)
	{
		if (args[i].type == T_REG && i > 1)
			ft_putchar('r');
		ft_printf("%d", (i < 2) ? CRG->reg[args[i].value - 1] : args[i].value);
		if (i + 1 < 3)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", a, b, a + b, CURRENT + a + b);
}

void		cw_ldi(void *core, t_list *carriage)
{
	t_arg	args[3];
	int		a;
	int		b;

	init_args((t_arg *)args, carriage, 3);
	a = get_operand(args[0], carriage, IDX_MOD);
	b = get_operand(args[1], carriage, IDX_MOD);
	CRG->reg[args[2].value - 1] = get_value_from_adr(carriage, a + b, IDX_MOD);
	if (((t_core *)core)->out == 4)
		ldi_print_process(carriage, (t_arg *)args, a, b);
	CRG->position = adr(CURRENT + 2 + args[0].size + args[1].size + args[2].size);
}
