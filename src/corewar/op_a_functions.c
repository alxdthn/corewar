/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_a_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 19:06:33 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/14 22:53:54 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_operand(t_arg arg, t_list *pc, int mod)
{
	if (arg.type == T_REG)
		return (PC->reg[arg.value - 1]);
	else if (arg.type == T_DIR)
		return (arg.value);
	else
		return (get_value_from_adr(pc, arg.value, mod));
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
	return (res);
}

int		get_value_from_adr(t_list *pc, int arg_value, int mod)
{
	int		pos;

	if (mod)
		pos = adr(PC->position + arg_value % mod);
	else
		pos = adr(PC->position + arg_value);
	return (get_value(PC->map, pos, sizeof(int)));
}

int		adr(int current_adr)
{
	if (current_adr >= MEM_SIZE)
		return (current_adr % MEM_SIZE);
	else if (current_adr < 0)
		return (MEM_SIZE + current_adr % MEM_SIZE);
	return (current_adr);
}

void		mov_pc(t_core *core, t_list *pc, int new_pos)
{
	if (core->visu_mod)
	{
		if (core->visual.map[CURRENT] >= 14)
			core->visual.map[CURRENT] -= 5;
		if (core->visual.map[new_pos] < 14) 
			core->visual.map[new_pos] += 5;
	}
	if (((t_core *)core)->out == 16)
		print_mov(pc, new_pos);
	PC->position = new_pos;
}
