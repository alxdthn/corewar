/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 22:04:27 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/06 23:17:57 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_arg_type(char byte)
{
	char	mask;

	mask = (byte & 0xC0) >> 6;
	if (mask == DIR_CODE)
		return (T_DIR);
	else if (mask == IND_CODE)
		return (T_IND);
	else if (mask == REG_CODE)
		return (T_REG);
	return (0);
}

int		get_arg_ofset(int arg, t_op *op)
{
	if (arg == T_DIR)
		return (DIR_OFSET);
	else if (arg == T_REG)
		return (REG_OFSET);
	else if (arg == T_IND)
		return (IND_OFSET);
	return (0);
}

t_op	*get_cmd(char *cmd)
{
	int		i;

	i = 0;
	while (op_tab[i].op_name)
	{
		if (ft_strequ(cmd, op_tab[i].op_name))
			return (&op_tab[i]);
		i++;
	}
	return (NULL);
}

int		get_arg_size(t_op *op, t_arg_type byte)
{
	int		size;
	int		i;
 
	size = 1;
	if (op->arg_count == 1 && op->args[0] == T_DIR)
		return (5);
	i = 0;
	while (i < op->arg_count)
	{
		if ((byte & 0xC0) == (REG_CODE << 6))
			size += REG_OFSET;
		else if ((byte & 0xC0) == (DIR_CODE << 6))
			size += DIR_OFSET;
		else if ((byte & 0xC0) == (IND_CODE << 6))
			size += IND_OFSET;
		byte <<= 2;
		i++;
	}
	return (size + op->arg_type);
}
