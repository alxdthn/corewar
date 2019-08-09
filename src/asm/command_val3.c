/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_val3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 17:38:38 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/09 17:39:26 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define COM ((t_comm *)tmp->content)
#define COM2 &((t_comm *)tmp->content)
#define KOS tmp[op_tab.arg_count - 1]
#define KOS2 ((t_label *)label->content)->name
#define KOS3 begin_c->content

void			add_arg(t_comm *com, char *str, t_as **all, t_op op_tab)
{
	int		x;
	int		c;
	char	*label;
	char	**tmp;

	x = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	(com)->arg_type = find_type_arg(all, str, 0, op_tab);
	tmp = ft_strsplit(str, SEPARATOR_CHAR);
	while (tmp[x])
	{
		c = find_c(tmp, x);
		(*all)->tmp_x = x;
		if (ft_isint(tmp[x] + c) && x == 0)
			(com)->arg_f = ft_atoi(tmp[x] + c);
		add_arg_help(tmp, all, str, com);
		x++;
	}
	ft_arraydel((void ***)&tmp);
}

int				check_arg(char *str, t_op op_tab, t_as **all)
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
			invalid_comm(all, &tmp, str);
	}
	if (!tmp[op_tab.arg_count - 1])
		invalid_comm(all, 0, str);
	str = ft_strstr(str, KOS) + ft_strlen(KOS);
	ft_arraydel((void ***)&tmp);
	if (!to_ignore(str, 0))
		return (0);
	return (1);
}

void			label_to_com(t_as **all, t_list *comm, t_list *tmp)
{
	tmp = (*all)->labels;
	while (tmp && (*all)->labels->next &&
	((t_label *)(*all)->labels->content)->link)
		(*all)->labels = (*all)->labels->next;
	while ((*all)->labels && ((t_label *)(*all)->labels->content)->link == 0)
	{
		((t_label *)(*all)->labels->content)->link = comm;
		(*all)->labels = (*all)->labels->next;
	}
	(*all)->labels = tmp;
}

void			add_command(t_as **all, t_list *tmp, char **f, char *str)
{
	int		counter;

	while (*str == ' ' || *str == '\t')
		str++;
	counter = check_command(str, f, all, find_counter(str));
	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		invalid_comm(all, &f, str);
	if (!(tmp->content = (t_comm *)malloc(sizeof(t_comm))))
	{
		free(tmp);
		invalid_comm(all, &f, str);
	}
	if (counter == 16 || *str == '\0' ||
	!check_arg(str + ft_strlen(op_tab[counter].op_name)
	+ 1, op_tab[counter], all))
		invalid_comm(all, 0, str);
	ft_bzero(COM, sizeof(t_comm));
	COM->instr = op_tab[counter].op_name;
	add_arg((COM), str + ft_strlen(op_tab[counter].op_name)
	+ 1, all, op_tab[counter]);
	COM->len = get_arg_size(&(op_tab[counter]), COM->arg_type);
	tmp->next = 0;
	ft_lstpushback(&(*all)->comm, tmp);
	label_to_com(all, tmp, 0);
}

void			create_lab(t_as **all, char *str, char **f, t_label **lab)
{
	char	*new;
	int		i;

	i = 0;
	while (ft_strindex(LABEL_CHARS, str[i]) != -1)
		i++;
	if (!(new = ft_strnew(i + 1)))
		invalid_comm(all, &f, str);
	if (!(*lab = (t_label *)malloc(sizeof(t_label))))
	{
		free(new);
		invalid_comm(all, &f, str);
	}
	ft_strncpy(new, str, i + 1);
	(*lab)->name = new;
	(*lab)->link = 0;
}
