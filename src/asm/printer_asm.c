/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_asm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 22:05:51 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/08 20:18:28 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	set_size_short(char *buf, int size, int i, int ofset)
{
	int		magic;

	magic = size;
	while (ofset)
		buf[i++] = magic >> (ofset -= 8);
}

void	write_operations(int s, char *str, t_comm *com, int counter)
{
	while (counter < 16)
	{
		if (!ft_strcmp(com->instr, op_tab[counter].op_name))
		//&& (*(com->instr + ft_strlen(op_tab[counter].op_name))) <= 32)
			break;
		counter++;
	}
	// ft_printf("arg_f - %d, instr - %d\n", com->arg_f, com->arg_type);
	str[s++] = op_tab[counter].op_code;
	if (op_tab[counter].arg_type)
		str[s++] = com->arg_type;
	while (com->arg_type)
	{
		if ((com->arg_type >= 192 || (com->arg_type >= 128 && op_tab[counter].t_dir_size == 2)))
		{
			s = s + 2;
			set_size_short(str, com->arg_f, s - 2, 16);
		}
		else if (com->arg_type >= 128)
		{
			s = s + 4;
			set_size_short(str, com->arg_f, s - 4, 32);
		}
		else if (com->arg_type >= 64)
			set_size_short(str, com->arg_f, s++, 8);
		// ft_printf("arg_f - %d, instr - %d\n", com->arg_f, s);
		com->arg_type <<= 2;
		com->arg_f = com->arg_s;
		com->arg_s = com->arg_t;
	}
}

void	print_to_bytecode(t_as *all, char *file, t_list *com, int size)
{
	int		fd;
	int		start;
	char	code_str[EXEC_CODE_OFSET + size + 1];

	if (!*all->name || !*all->comment)
	{
		ft_printf("Invalid name or comment\n");
		return ;
	}
	fd = print_basic(all, file, code_str, size);
	// ft_printf("arg_f - %d\n", ((t_comm *)com->content)->arg_f);
	start = EXEC_CODE_OFSET;
	while (com)
	{
		write_operations(start, code_str, ((t_comm *)com->content), 0);
		start += ((t_comm *)com->content)->len;
		com = com->next;
	}
	write(fd, code_str, EXEC_CODE_OFSET + size);
	close(fd);
//	print_memory(code_str, EXEC_CODE_OFSET + size);
}

int		code_size(t_list *com, int res)
{
	while (com)
	{
		res += ((t_comm *)com->content)->len;
		com = com->next;
	}
	return (res);
}
