/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:12:57 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/15 16:38:52 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include <stdio.h>
# include <unistd.h>
# include <ncurses.h>

# define MEM_ERROR "Error: mem alloc error!"

# define STR(var) ((char *)var->content)
# define MAGIC_SIZE sizeof(int)
# define NAME_OFSET MAGIC_SIZE
# define CODE_SIZE_OFSET (NAME_OFSET + PROG_NAME_LENGTH + sizeof(int))
# define COMMENT_OFSET (CODE_SIZE_OFSET + sizeof(int))
# define EXEC_CODE_OFSET (COMMENT_OFSET + COMMENT_LENGTH + sizeof(int))
# define FALSE 0
# define TRUE 1

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

t_op    			g_op_tab[17];

void			print_memory(const char *mem, ssize_t size);
int				adr(int current_adr);
int				get_int(int *pos);
t_op			*get_cmd(char *cmd);
int				get_arg_type(char arg_byte);
int				get_arg_code(char arg_type);
int				get_arg_ofset(int arg_type, t_op *op);
int				get_function_size(char arg_byte, t_op *op);
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

# define PRINT_ARG_OFSET 30
# define PRINT_NAME_OFSET 10
# define CHAR_FOR_NAME 10
# define REG_OFSET 1
# define IND_OFSET 2
# define DIR_OFSET op->t_dir_size
# define PC ((t_pc *)pc->content)
# define PC_NEXT ((t_pc *)pc->next->content)
# define OPERATION_CODE 0
# define ARG_BYTE PC->position + 1
# define PROCESS PC->op_info->process
# define BYTE(pos) (PC->map[adr(pos)])
# define CURRENT PC->position
# define ARG_TYPE PC->op_info->arg_type
# define OPER_ARGS PC->op_info->args
# define GET_VAL(pos, size) (ft_reverse_bytes(*((size *)(pos)), sizeof(size)))
# define FT_ABS(X)		(((X) < 0) ? (-(X)) : (X))
# define ESC 27
# define SPACE 32

# define COLOR_GRAY				8
# define GRAY					9
# define GREEN					10
# define YELLOW					11
# define REDD					12
# define CYAN					13
# define GRAY_CURSOR			14
# define GREEN_CURSOR			15
# define YELLOW_CURSOR			16
# define RED_CURSOR				17
# define CYAN_CURSOR			18
# define LIVE_GREEN				19
# define LIVE_YELLOW			20
# define LIVE_RED				21
# define LIVE_CYAN				22

static int g_colors_players[15] = {
	COLOR_PAIR(GRAY),
	COLOR_PAIR(GREEN),
	COLOR_PAIR(YELLOW),
	COLOR_PAIR(REDD),
	COLOR_PAIR(CYAN),
	COLOR_PAIR(GRAY_CURSOR),
	COLOR_PAIR(GREEN_CURSOR),
	COLOR_PAIR(YELLOW_CURSOR),
	COLOR_PAIR(RED_CURSOR),
	COLOR_PAIR(CYAN_CURSOR)
};

typedef struct		s_arg
{
	int				type;
	int				size;
	int				value;
}					t_arg;

typedef struct		s_player
{
	int				code_size;
	int				nb;
	int				id;
	int				start_position;
	char			*name;
	char			*comment;
	char			*exec_code;
}					t_player;

typedef struct		s_pc
{
	t_bool			carry;
	int				reg[REG_NUMBER];
	int				nb;
	int				cycle;
	int				cycle_for_op;
	int				position;
	unsigned char	*map;
	t_player		*owner;
	t_op			*op_info;
	char			op;
}					t_pc;

typedef struct		s_attr
{
	int				index;
	int				light;
	int				live_player_id;
	char			pc_here;
}					t_attr;

typedef struct			s_visual
{
	WINDOW				*win_arena;
	WINDOW				*win_info;
    t_attr				attrs[MEM_SIZE];
    char                button;
    int                 running;
    int					row;
    int					col;
}						t_visual;

typedef struct		s_core
{
	unsigned char	map[MEM_SIZE];
	t_list			*input;
	t_list			*pcs;
	t_player		*players[MAX_PLAYERS + 1];
	t_player		*last_player;
	int				cycle_to_die;
	int				live_count;
	int				game_check_count;
	int				war_count;
	int				current_process_count;
	int				global_process_count;
	unsigned long	cycle_after_start;
	int				d;

	int				flag;

	int				dump;
	int				out;
	int				print_pc;
	int				print_aff;
	int				death;
	int				arg_ofset;
	int 			visu_mod;
	t_visual		visual;
    int				dump_print_mode;
}					t_core;

int					put_usage(int fd);
void				cw_clear_exit(t_core *core, const char *message, const int fd);
void				read_input(t_core *core, int ac, char **av);
void				init_players(t_core *core, int ac, char **av);
void				init_processes(t_core *core);
int					validate_operation(t_list *pc);
void 				game_cycle(t_core *core);
void				game_check(t_core *core, int *cycle_to_die);

void				init_args(t_arg *args, t_list *pc, int count);
int					get_operand(t_arg arg, t_list *pc, int mod);

void				set_value(unsigned char *mem, int pos, int size, int value);
void				mov_pc(t_core *core, t_list *pc, int new_pos);

int					get_value(unsigned char *mem, int pos, int size);
int					get_value_from_adr(t_list *pc, int arg_value, int mod);

void				cw_live(void *core, t_list *pc);
void				cw_ld(void *core, t_list *pc);
void				cw_st(void *core, t_list *pc);
void				cw_add(void *core, t_list *pc);
void				cw_sub(void *core, t_list *pc);
void				cw_and(void *core, t_list *pc);
void				cw_or(void *core, t_list *pc);
void				cw_xor(void *core, t_list *pc);
void				cw_zjmp(void *core, t_list *pc);
void				cw_ldi(void *core, t_list *pc);
void				cw_sti(void *core, t_list *pc);
void				cw_fork(void *core, t_list *pc);
void				cw_lld(void *core, t_list *pc);
void				cw_lldi(void *core, t_list *pc);
void				cw_lfork(void *core, t_list *pc);
void				cw_aff(void *core, t_list *pc);

void				print_info_header(t_list *pc);
void				print_warriros(t_core *core);
void				print_dump(t_core *core, int bar, int exit);
void				print_input(t_list *tmp);
void				print_mov(t_list *pc, int new);
void				print_processes(t_core *core, t_list *pc, int count);
int					print_process_header(t_core *core, t_list *pc);

void				init_visual(t_core *core);
void		        show_fight_field(t_core *core);
void				colorize_mem(t_core *core, int pos, int color);
void 				create_frame(t_core *core);
void				draw(t_core *core);


#endif
