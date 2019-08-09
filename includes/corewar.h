/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:12:57 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/09 17:41:31 by skrystin         ###   ########.fr       */
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
typedef char		t_bool;

typedef struct		s_op
{
	char			*op_name;
	char			arg_count;
	char			args[3];
	char			op_code;
	int				cycle;
	char			*description;
	char			arg_type;
	char			t_dir_size;
	char			carry;
	void			(*process)(void *, t_list *);
}					t_op;

t_op    			op_tab[17];

void			print_memory(char *mem, ssize_t size);
int				mem_rev(int mem);
t_op			*get_cmd(char *cmd);
int				get_arg_type(char arg_byte);
int				get_arg_code(char arg_type);
int				get_arg_ofset(int arg_type, t_op *op);
int				get_arg_size(t_op *op, char arg_byte);
void			print_operation_info(char *position);
/*
**	asm part
*/
typedef	struct		s_as
{
	char			name[PROG_NAME_LENGTH + 1];
	int				name_i;
	char			comment[COMMENT_LENGTH + 1];
	int				com_i;
	char			read;
	int				comand_n;
	int				tmp_x;
	t_list			*comm;
	t_list			*labels;
}					t_as;

typedef	struct		s_comm
{
	char			*instr;
	unsigned char	arg_type;
	int				arg_f;
	int				arg_s;
	int				arg_t;
	char			*label_f;
	char			*label_s;
	char			*label_t;
	int				len;
}					t_comm;

typedef	struct		s_label
{
	char			*name;
	struct	s_list	*link;	
}					t_label;

int				to_ignore(char *str, int x);
void			ft_write_it(t_as **all, int *y, char **f, int x);
void			add_names(t_as **all, int *y, char **f, int x);
void			check_to_valid(char *str, int x, t_as **all, char **f);
int				check_command(char *str, char **f, t_as **all, int counter);
unsigned char	find_type_arg(t_as **all, char *str, int i, t_op op_tb);
void			add_arg(t_comm *com, char *str, t_as **all, t_op op_tab);
int				check_arg(char *str, t_op op_tab, t_as **all);
void			label_to_com(t_as **all, t_list *comm, t_list *tmp);
void			add_command(t_as **all, t_list *tmp, char **f, char *str);
int				add_label(t_as **all, char **f, char *str, int y);
void			label_to_nbr(t_as **all, t_list *label, t_list *begin_c, t_list	*tmp);
int				len_to_label(t_list *dst, t_list *label, char *find, t_as **all);
int				print_basic(t_as *all, char *file, char *head, int size);
void			set_size_short(char *buf, int size, int i, int ofset);
void			write_operations(int s, char *str, t_comm *com, int counter);
void			print_to_bytecode(t_as *all, char *file, t_list *com, int size);
int				code_size(t_list *com, int res);
void			del_com(t_as **all, t_list *comm);
void			del_labels(t_as **all, t_list *lab);
void			delete_asm_all(t_as **all, char **file, char ***f);
void			first_error(char *str, char *file, char **todel);
void			valid_errors(char *line, char ***todel, t_as **all, int flag);
void			invalid_comm(t_as **all, char ***todel, char *str);
int				find_counter(char *str);
int				check_command(char *str, char **f, t_as **all, int counter);
int				find_c(char **tmp, int x);
void			add_arg_help(char **tmp, t_as **all, char *str, t_comm *com);
void			add_arg(t_comm *com, char *str, t_as **all, t_op op_tab);
int				check_arg(char *str, t_op op_tab, t_as **all);
void			label_to_com(t_as **all, t_list *comm, t_list *tmp);
void			create_lab(t_as **all, char *str, char **f, t_label **lab);

/*
**	corewar part
*/

#define USAGE "usage:"
#define CRG ((t_carriage *)carriage->content)
#define CRG_NEXT ((t_carriage *)carriage->next->content)
#define OPERATION_CODE 0
#define ARG_BYTE 1

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
	char			live;
	int				reg[REG_NUMBER];
	int				nb;
	int				cycle;
	int				cycle_for_op;
	int				position;
	int				ofset;
	char			*op;
	t_warrior		*owner;
	t_op			*op_info;
	t_bool			carry;
}					t_carriage;

typedef struct		s_core
{
	char			map[MEM_SIZE];
	t_list			*input;
	t_list			*carriages;
	t_warrior		*warriors[MAX_PLAYERS + 1];
	int				cycle_to_die;
	int				cycle_to_die_delta;
	int				live_count;
	int				live_check_count;
	int				war_count;
	unsigned long	cycle_after_start;
}					t_core;

void				cw_clear_exit(t_core *core, const char *message, const int fd);
void				read_input(t_core *core, const int ac, const char **av);
void				init_warriors(t_core *core);
void				init_carriages(t_core *core);
int					validate_operation(t_core *core, t_list *carriage);
void 				start_game(t_core *core);

int					get_arg_value(t_list *carriage, char *op, char arg_byte, char *map);
int					get_arg_value_debug(t_list *carriage, char *op, char arg_byte, char *map);
void				cw_live(void *core, t_list *carriage);
void				cw_ld(void *core, t_list *carriage);
void				cw_st(void *core, t_list *carriage);
void				cw_add(void *core, t_list *carriage);
void				cw_sub(void *core, t_list *carriage);
void				cw_and(void *core, t_list *carriage);
void				cw_or(void *core, t_list *carriage);
void				cw_xor(void *core, t_list *carriage);
void				cw_zjmp(void *core, t_list *carriage);
void				cw_ldi(void *core, t_list *carriage);
void				cw_sti(void *core, t_list *carriage);
void				cw_fork(void *core, t_list *carriage);
void				cw_lld(void *core, t_list *carriage);
void				cw_lldi(void *core, t_list *carriage);
void				cw_lfork(void *core, t_list *carriage);
void				cw_aff(void *core, t_list *carriage);

void				print_warriros(t_core *core);
void				print_map(t_core *core, int bar);
void				print_input(t_list *tmp);
void				print_carriage(t_list *carriage);

#endif
