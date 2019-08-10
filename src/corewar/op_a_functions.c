/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_a_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 19:06:33 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/10 19:16:53 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_args(t_arg *args, int count)
{
	int		i;
	char	type;

	i = 0;
	while (i < count)
	{
		if (args[i].type == T_DIR)
			ft_putchar('%');
		else if (args[i].type == T_REG)
			ft_putchar('r');
		ft_printf("%d(%d) ", args[i].value, args[i].size);
		i++;
	}
	ft_putchar('\n');
}

void	init_args(t_arg *args, t_list *carriage, int count)
{
	int		position;

	args[0].type = (ARG_TYPE) ? get_arg_type(adr(ARG_BYTE)) : OPER_ARGS[0];
	args[0].size = get_arg_ofset(args[0].type, CRG->op_info);
	position = ARG_BYTE + ARG_TYPE;
	args[0].value = get_value(CRG->map, adr(position), args[0].size);
	if (count > 1)
	{
		args[1].type = get_arg_type(adr(ARG_BYTE) << 2);
		args[1].size = get_arg_ofset(args[1].size, CRG->op_info);
		position += args[0].size;
		args[1].value = get_value(CRG->map, adr(position), args[1].size);
	}
	if (count > 2)
	{
		args[2].type = get_arg_type(adr(ARG_BYTE) << 4);
		args[2].size = get_arg_ofset(args[1].size, CRG->op_info);
		position += args[1].size;
		args[2].value = get_value(CRG->map, adr(position), args[2].size);
	}
}
