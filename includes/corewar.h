/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:12:57 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/05 14:53:25 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "ft_printf.h"
# include "op.h"

# define MEM_ERROR "Error: mem alloc error!"
# define OPEN_ERR "Error: can't open file!"
# define INPUT_ERR "Error: input error!"

# define STR(var) ((char *)var->content)

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

void			print_memory(char *mem, ssize_t size);
/*
**	asm part
*/
		
/*
**	corewar part
*/
typedef struct	s_core
{
	char		map[MEM_SIZE];
	t_list		*input;
	void		(*exit)(struct s_core *, const char *, const int);
}				t_core;

void			cw_clear_exit(t_core *core, const char *message, const int fd);
void			print_map(char *map);
void			print_input(t_list *tmp);

#endif
