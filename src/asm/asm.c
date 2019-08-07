/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:10:58 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 15:08:07 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
# define COM ((t_comm *)tmp->content)
# define COM2 &((t_comm *)tmp->content)

int		check_command(char *str, char **f, t_as **all)
{
	int		counter;
	int		after;
	char	**args;

	counter = 0;
	while (counter < 16)
	{
		if (ft_strstr(str, op_tab[counter].op_name) == str
		&& (*(str + ft_strlen(op_tab[counter].op_name))) <= 32)
			break;
		counter++;
	}
	// if (ft_strstr(str, op_tab[7].op_name))
	// 	ft_printf("\nstr - %s,  %d\n", ft_strstr(str, op_tab[7].op_name) + ft_strlen(op_tab[7].op_name),
	// 	*(str + ft_strlen(op_tab[7].op_name)));
	if (counter == 16)
		exit(0);//do more
	str = str + ft_strlen(op_tab[counter].op_name);
	if ((after = ft_strccount(str, SEPARATOR_CHAR)) + 1 != op_tab[counter].arg_count)
		exit(0);//do more
	while (after--)
		str = str + ft_strindex(str, SEPARATOR_CHAR) + 1;
	// ft_printf("hi - %s", str);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == 'r' || *str == '-' || *str == '%')
		str++;
	while (ft_isalnum(*str))
		str++;
	if (!to_ignore(str, 0) && *str != LABEL_CHAR)
		exit(0);//do more
	// ft_printf("hi - %s", str);
	return (counter);
}

unsigned char	find_type_arg(char *str, int i, t_op op_tb)
{
	unsigned char	res;
	int				arg;

	arg = 0;
	res = 0;
	while (str && arg < op_tb.arg_count)
	{
		if (*str == 'r' && (op_tb.args[arg] & T_REG) == T_REG)
		{
			res = res | REG_CODE;
			res <<= 2;
		}
		else if (*str == '%' && (op_tb.args[arg] & T_DIR) == T_DIR)
		{
			res = res | DIR_CODE;
			res <<= 2;
		}
		else if ((ft_isdigit(*str) || *str == '-' || *str == ':') && (op_tb.args[arg] & T_IND) == T_IND)
		{
			res = res | IND_CODE;
			res <<= 2;
		}
		else
		{
			ft_printf("i dont know type of this - %s", str);
			exit(0);//do more
		}
		arg++;
		str += ft_strindex(str, SEPARATOR_CHAR) + 1;
		while (*str == ' ' || *str == '\t')
			str++;
	}
	res <<= ((3 - op_tb.arg_count) * 2);
	//		ft_printf("arg_type - %d", op_tb.arg_count);
	//ft_printf("byte - %hhx", res);
	return (res);
}

void	add_arg(t_comm *com, char *str, char **tmp, t_op op_tab)
{
	int	x;
	int	c;
	char *label;

	x = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	tmp = ft_strsplit(str, SEPARATOR_CHAR);
	// ft_printf("This bad arg is - %s\n", tmp[x] + c);
//	if (op_tab.arg_type)
	(com)->arg_type = find_type_arg(str, 0, op_tab);
	while (tmp[x])
	{
		c = 0;
		while (tmp[x][c] == ' ' || tmp[x][c] == '\t')
			c++;
		if (tmp[x][c] == 'r' || tmp[x][c] == '%')
			c++;
		if (ft_isint(tmp[x] + c) && x == 0)
			(com)->arg_f = ft_atoi(tmp[x] + c);
		if (ft_isint(tmp[x] + c) && x == 1)
			(com)->arg_s = ft_atoi(tmp[x] + c);
		if (ft_isint(tmp[x] + c) && x == 2)
			(com)->arg_t = ft_atoi(tmp[x] + c);
		if (!ft_isint(tmp[x] + c) && *(tmp[x] + c) != LABEL_CHAR)
		{
			ft_printf("This bad arg is - %s", tmp[x] + c);
			exit(0);//do more
		}
		if (!ft_isint(tmp[x] + c) && *(tmp[x] + c) == LABEL_CHAR)
		{
			if (!(label = ft_strnew(ft_strlen(tmp[x] + c))))
				exit(0);//do more
			ft_strcpy(label, tmp[x] + c);
			// ft_printf("\n\nIM WORK EEEE - %s, nb - %d\n\n", label, x);
			if (x == 0)
				(com)->label_f = label;
			if (x == 1)
				(com)->label_s = label;
			if (x == 2)
				(com)->label_t = label;
		}
		x++;
	}
	ft_arraydel((void ***)&tmp);
}

int		check_arg(char *str, t_op op_tab)
{
	char	**tmp;
	int		i;
	int		x;

	if (ft_strccount(str, SEPARATOR_CHAR) != op_tab.arg_count - 1)
		return (0);
	tmp = ft_strsplit(str, SEPARATOR_CHAR);
	i = 0;
	while (tmp[i])
	{
		x = 0;
		while (tmp[i][x] == ' ' || tmp[i][x] == '\t')
			x++;
		if (tmp[i][x] == '%' || (tmp[i][x] == 'r' && tmp[i][x + 1] != '-'))
			x++;
		if (!ft_isint(tmp[i++] + x) && *(tmp[i - 1] + x) != LABEL_CHAR)
		{
			ft_printf("this - %s", tmp[--i]);
			ft_arraydel((void ***)&tmp);
			return (0);
		}
	}
	str = ft_strstr(str, tmp[op_tab.arg_count - 1]) + ft_strlen(tmp[op_tab.arg_count - 1]);
//	ft_printf("this - %s", str);
	ft_arraydel((void ***)&tmp);
	if (!to_ignore(str, 0))
		return (0);
//	ft_printf("this - %s", str);
	return (1);
}

void	label_to_com(t_as **all, t_list *comm, t_list *tmp)
{
	tmp = (*all)->labels;
	while (tmp && (*all)->labels->next)
		(*all)->labels = (*all)->labels->next;
	// if ((*all)->labels)
	// 	ft_printf("HI - %s", ((t_label *)(*all)->labels->content)->link);
	if ((*all)->labels && ((t_label *)(*all)->labels->content)->link == 0)
	{
		// ft_printf("HI");
		((t_label *)(*all)->labels->content)->link = comm;
	}
	(*all)->labels = tmp;
}

void	add_command(t_as **all, t_list *tmp, char **f, char *str)
{
	int		counter;

	while (*str == ' ' || *str == '\t')
		str++;
	counter = check_command(str, f, all);
	// ft_printf("arg - %s", str);
	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		exit(0);// do more
	if (!(tmp->content = (t_comm *)malloc(sizeof(t_comm))))
		exit(0);//do more
	// ft_printf("arg - %s\n", str);
	if (counter == 16 || *str == '\0' ||
	!check_arg(str + ft_strlen(op_tab[counter].op_name) + 1, op_tab[counter]))
		exit(0);// do more
	// ft_printf("arg - %s", str);
	ft_bzero(COM, sizeof(t_comm));
	COM->instr = op_tab[counter].op_name;
	//ft_printf("arg - %s\n", str);
	add_arg((COM), str + ft_strlen(op_tab[counter].op_name) + 1, 0, op_tab[counter]);
	COM->len = get_arg_size(&(op_tab[counter]), COM->arg_type);
	//ft_printf("%d  byte - %hhx", COM->len, COM->arg_type);
	// ft_printf("arg - %s", str);
	tmp->next = 0;
	ft_lstpushback(&(*all)->comm, tmp);
	label_to_com(all, tmp, 0);
}

int		add_label(t_as **all, char **f, char *str, int y)
{
	char	*new;
	t_list	*tmp;
	int		i;
	t_label	*lab;

	i = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	while (ft_strindex(LABEL_CHARS, str[i]) != -1)
		i++;
	if (str[i] != LABEL_CHAR)
		return (1);
	if (!(new = ft_strnew(i + 1)))
		exit(0);//do more
	if (!(lab = (t_label *)malloc(sizeof(t_label))))
		exit(0);//do more
	ft_strncpy(new, str, i + 1);
	lab->name = new;
	lab->link = 0;
	if (!(tmp = ft_lstnew(lab, sizeof(t_label))))
		exit(0);//do more
	ft_lstpushback(&((*all)->labels), tmp);
	// ft_printf("\nlabel - %s\n", ((t_label *)tmp->content)->name);
	while (i >= 0)
		f[y][i--] = ' ';
	return (1);
}

int		len_to_label(t_list *dst, t_list *label, char *find, t_list *begin_c)
{
	t_list	*src;
	int		flag;
	int		res;

	flag = 0;
	res = 0;
	while (label && (ft_strncmp(((t_label *)label->content)->name, find + 1, ft_strlen(find + 1))
	|| ft_strlen(find) != ft_strlen(((t_label *)label->content)->name)))
		label = label->next;
	if (!label)
	{
		ft_printf("This bad label is - %s\n", find);
		exit(0);
	}
	src = ((t_label *)label->content)->link;
	//if (dst->content)
	ft_printf("\nSRC that - %s, DST that - %s\n", ((t_comm *)src->content)->instr, ((t_comm *)dst->content)->instr);
	while (begin_c)
	{
		if (begin_c == src && flag == 0)
			flag = -1;
		else if (begin_c->content == dst->content && flag == 0)
		{
			ft_printf("HERE I GO AGAIN\n");
			flag = 1;
		}
		else if ((begin_c == src || begin_c->content == dst->content) && flag != 0)
		{
			// ft_printf("IS IT WORK???????\n");
			flag = 0;
		}
		res += flag * (((t_comm *)begin_c->content)->len);
		begin_c = begin_c->next;
	}
	ft_printf("I find this - %d to that name - %s\n", res, find);
	return (res);
}

void	label_to_nbr(t_as **all, t_list *label, t_list *begin_c, t_list	*tmp)
{
	tmp = (*all)->comm;
	while (tmp)
	{
		// if (*COM->instr == 'f')
		// 	ft_printf("FIND THIS MASAFUKER %d\n", COM->arg_f);
		if (COM->label_f || COM->label_s || COM->label_t)
		{
			if (COM->label_f)
			{
				COM->arg_f = len_to_label(tmp, label, COM->label_f, begin_c);
				free(COM->label_f);
				COM->label_f = NULL;
			}
			if (COM->label_s)
			{
				COM->arg_s = len_to_label(tmp, label, COM->label_s, begin_c);
				free(COM->label_s);
				COM->label_s = NULL;
			}
			if (COM->label_t)
			{
				COM->arg_t = len_to_label(tmp, label, COM->label_t, begin_c);
				free(COM->label_t);
				COM->label_t = NULL;
			}
				//ft_printf("HI");
		}
		else
			tmp = tmp->next;
	}
	(*all)->comm = begin_c;
}

void	translator(char **f, int y, int x, t_as *all)
{
	if (!(all = (t_as *)malloc(sizeof(t_as))))
	{
		ft_arraydel((void ***)&f);
		exit(0);
	}
	ft_bzero(all, sizeof(t_as));
	while (f[y])
	{
		check_to_valid(f[y], 0, &all, f);
		if (to_ignore(f[y], 0) && y++ != -2)
			continue;
		ft_printf("%s\n", f[y]);
		if (ft_strstr(f[y], NAME_CMD_STRING) || ft_strstr(f[y], COMMENT_CMD_STRING) || all->read)
			add_names(&all, &y, f, 0);
		else if (add_label(&all, f, f[y], y) && !to_ignore(f[y], 0))
			add_command(&all, 0, f, f[y]);
		y++;
	}
	label_to_nbr(&all, all->labels, all->comm, 0);
	ft_printf("name - %s, int_n -%d comment - %s", all->name, all->name_i, all->comment);
	ft_printf("\ncomm - %s\n", ((t_comm *)all->comm->content)->instr);
//	ft_printf("\nLabel - %s\n", ((t_comm *)((t_label *)all->labels->next->next->content)->name));
}

int		main(int ac, char **av)
{
	char	*file;
	char	**per_str;
	int		fd;

	if (ac == 1)
		return (0);
	if ((fd = open(av[ac - 1],O_RDONLY)) < 3)
		return (0);
	if (ft_read_to_str(fd, &file, 10) == -1 || !ft_strlen(file) || file[ft_strlen(file) - 1] != '\n')
		return (0);// надо обработать, и предыдущие тоже
//	ft_printf("%c\n", file[ft_strlen(file) - 1]);
	translator(per_str = ft_strsplit(file, '\n'), 0, 0, 0);
	free(file);
	// fd = 0;
	// while (per_str[fd])
	// 	ft_printf("%s\n", per_str[fd++]);
	// return (0);
}
