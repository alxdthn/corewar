/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:12:57 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/05 20:05:47 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "ft_printf.h"
# include "op.h"

# define MEM_ERROR "Error: mem alloc error!"

# define STR(var) ((char *)var->content)
# define NAME_OFSET 4
# define COMMENT_OFSET 140
# define CODE_SIZE_OFSET 34
# define EXEC_CODE_OFSET 2192
# define FALSE 0
# define TRUE 1

/*
**	common part
*/
typedef char	t_bool;

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
int				mem_rev(int mem);
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

#define USAGE "usage:"
#define CARRIAGE ((t_carriage *)tmp->content)

typedef struct		s_warrior
{
	int				code_size;
	int				nb;
	int				start_position;
	char			*name;
	char			*comment;
	char			*exec_code;
}					t_warrior;

typedef struct		s_carriage
{
	int				reg[REG_NUMBER];
	int				nb;
	int				cycle;
	int				cycle_for_op;
	int				position;
	int				ofset;
	char			op;
	t_bool			carry;
}					t_carriage;

typedef struct		s_core
{
	unsigned char	map[MEM_SIZE];
	t_list			*input;
	t_list			*carriages;
	t_warrior		*warriors[MAX_PLAYERS + 1];
	int				war_count;
}					t_core;

void				cw_clear_exit(t_core *core, const char *message, const int fd);
void				read_input(t_core *core, const int ac, const char **av);
void				init_warriors(t_core *core);

void				print_warriros(t_core *core);
void				print_map(unsigned char *map);
void				print_input(t_list *tmp);
void				print_carriage(t_list *carriage);


#endif
