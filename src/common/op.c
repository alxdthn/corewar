/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/08/04 15:17:36 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

t_op    		op_tab[16] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 4, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 4, 1},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 4, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 4, 1},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 1},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 4, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 4, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 4, 1},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 2, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 2, 0},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 2, 0},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 2, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 4, 1},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 2, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 2, 0},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 4, 0}
};
