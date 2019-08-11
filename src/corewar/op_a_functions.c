/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_a_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 19:06:33 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/11 21:26:18 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_operand(t_arg arg, t_list *carriage, int mod)
{
	if (arg.type == T_REG)
		return (CRG->reg[arg.value - 1]);
	else if (arg.type == T_DIR)
		return (arg.value);
	else
		return (get_value_from_adr(carriage, arg.value, mod));
}

void	set_value(unsigned char *mem, int pos, int size, int value)
{
	int		i;

	i = pos;
	while (size--)
	{
		if (i >= MEM_SIZE)
			i = 0;
		mem[i++] = value >> 24;
		value <<= 8;
	}
}

void	set_value_to_adr(t_list *carriage, int arg_value, int mod, int value)
{
	if (mod)
		set_value(CRG->map, adr(CURRENT + arg_value % mod), sizeof(int), value);
	else
		set_value(CRG->map, adr(CURRENT + arg_value), sizeof(int), value);
}


int		get_value(unsigned char *mem, int pos, int size)
{
	int		i;
	int		res;
	int		tmp_size;

	i = pos;
	res = 0;
	tmp_size = size;
	while (size--)
	{
		if (i >= MEM_SIZE)
			i = 0;
		res <<= 8;
		res |= mem[i++];
	}
	if (tmp_size == 2)
		return ((short)res);
	else if (tmp_size == 1)
		return ((char)res);
	return (res);
}

int		get_value_from_adr(t_list *carriage, int arg_value, int mod)
{
	int		pos;

	if (mod)
		pos = adr((CRG->position + arg_value) % mod);
	else
		pos = adr(CRG->position + arg_value);
	return (get_value(CRG->map, pos, sizeof(int)));
}

int		adr(int current_adr)
{
	if (current_adr >= MEM_SIZE)
		return (current_adr % MEM_SIZE);
	else if (current_adr < 0)
		return (MEM_SIZE + current_adr % MEM_SIZE);
	return (current_adr);
}

void	print_process(t_list *carriage, t_arg *args, int arg_count)
{
	int		i;

	ft_printf("P%5d | %s ", CRG->nb, CRG->op_info->op_name);
	i = 0;
	while (i < arg_count)
	{
		if (args[i].type == T_REG)
			ft_putchar('r');
		ft_printf("%d", args[i].value);
		if (i + 1 < arg_count)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void	init_args(t_arg *args, t_list *carriage, int count)
{
	int		position;
	char	arg_byte;

	arg_byte = (ARG_TYPE) ? BYTE(ARG_BYTE) : (get_arg_code(OPER_ARGS[0]) << 6);
	args[0].type = get_arg_type(arg_byte);
	args[0].size = get_arg_ofset(args[0].type, CRG->op_info);
	position = CURRENT + 1 + ARG_TYPE;
	args[0].value = get_value(CRG->map, adr(position), args[0].size);
	if (count > 1)
	{
		args[1].type = get_arg_type(arg_byte << 2);
		args[1].size = get_arg_ofset(args[1].type, CRG->op_info);
		position += args[0].size;
		args[1].value = get_value(CRG->map, adr(position), args[1].size);
	}
	if (count > 2)
	{
		args[2].type = get_arg_type(arg_byte << 4);
		args[2].size = get_arg_ofset(args[2].type, CRG->op_info);
		position += args[1].size;
		args[2].value = get_value(CRG->map, adr(position), args[2].size);
	}
}
