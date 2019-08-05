/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:12:57 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/05 14:36:19 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "ft_printf.h"
# include "op.h"
/*
**	common part
*/
typedef struct	s_op
{
	char		*op_name;
	char		arg_count;
	char		args[3];
	char		op_code;
	int			cycle;
	char		*description;
	char		arg_type;
	char		t_dir_size;
	char		carry;
}				t_op;

t_op    		op_tab[17];

void			print_memory(char *av);
/*
**	asm part
*/
typedef	struct	s_as
{
	char		name[129];
	int			name_i;
	char		comment[2049];
	int			com_i;
	char		read;
	int			size;
	t_list		*comm;
}				t_as;
/*
**	corewar part
*/
typedef struct	s_core
{
	char		map[MEM_SIZE];
	t_list		*input;
}				t_core;

#endif
