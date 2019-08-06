/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:12:57 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/06 21:19:55 by skrystin         ###   ########.fr       */
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
