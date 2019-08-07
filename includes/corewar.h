/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:12:57 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:06:55 by skrystin         ###   ########.fr       */
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
# define REG_OFSET 1
# define IND_OFSET 2
# define DIR_OFSET op->t_dir_size

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
int				get_arg_code(char byte);
int				get_arg_type(char byte);
int				get_arg_size(t_op *op, t_arg_type byte);
t_op			*get_cmd(char *cmd);
int				get_arg_ofset(int arg, t_op *op);
void			print_operation_info(char *position);
/*
**	asm part
*/
typedef	struct	s_as
{
	char		name[PROG_NAME_LENGTH + 1];
	int			name_i;
	char		comment[COMMENT_LENGTH + 1];
	int			com_i;
	char		read;
	int			comand_n;
	t_list		*comm;
	t_list		*labels;
}				t_as;

typedef	struct	s_comm
{
	char		*instr;
	unsigned char		arg_type;
	int			arg_f;
	int			arg_s;
	int			arg_t;
	char		*label_f;
	char		*label_s;
	char		*label_t;
	int			len;
}				t_comm;

typedef	struct	s_label
{
	char			*name;
	struct	s_list	*link;	
}				t_label;

int				to_ignore(char *str, int x);
void			ft_write_it(t_as **all, int *y, char **f, int x);
void			add_names(t_as **all, int *y, char **f, int x);
void			check_to_valid(char *str, int x, t_as **all, char **f);
int				check_command(char *str, char **f, t_as **all);
unsigned char	find_type_arg(char *str, int i, t_op op_tb);
void			add_arg(t_comm *com, char *str, char **tmp, t_op op_tab);
int				check_arg(char *str, t_op op_tab);
void			label_to_com(t_as **all, t_list *comm, t_list *tmp);
void			add_command(t_as **all, t_list *tmp, char **f, char *str);
int				add_label(t_as **all, char **f, char *str, int y);
void			label_to_nbr(t_as **all, t_list *label, t_list *begin_c, t_list	*tmp);
int				len_to_label(t_list *dst, t_list *label, char *find, t_list *begin_c);
int				print_basic(t_as *all, char *file, char *head, int size);
void			set_size_short(char *buf, int size, int i, int ofset);
void			write_operations(int s, char *str, t_comm *com, int counter);
void			print_to_bytecode(t_as *all, char *file, t_list *com, int size);
int				code_size(t_list *com, int res);

/*
**	corewar part
*/

#define USAGE "usage:"
#define CRG ((t_carriage *)carriage->content)
#define OPERATION_CODE 0
#define ARG_BYTE 1

typedef union			u_arg_byte
{
	char				byte;
	struct
	{
		unsigned char	a4 : 2;
		unsigned char	a3 : 2;
		unsigned char	a2 : 2;
		unsigned char	a1 : 2;
	}					arg;
}						t_arg_byte;

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
	char			*op;
	t_op			*op_info;
	t_bool			carry;
}					t_carriage;

typedef struct		s_core
{
	char			map[MEM_SIZE];
	t_list			*input;
	t_list			*carriages;
	t_warrior		*warriors[MAX_PLAYERS + 1];
	int				war_count;
}					t_core;

void				cw_clear_exit(t_core *core, const char *message, const int fd);
void				read_input(t_core *core, const int ac, const char **av);
void				init_warriors(t_core *core);
void				init_carriages(t_core *core);
int					validate_operation(t_list *carriage);

void				print_warriros(t_core *core);
void				print_map(unsigned char *map);
void				print_input(t_list *tmp);
void				print_carriage(t_list *carriage);



#endif
