/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:10:58 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 21:02:44 by skrystin         ###   ########.fr       */
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
	print_memory(code_str, EXEC_CODE_OFSET + size);
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

void	translator(char **f, int y, char *file, t_as *all)
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
	ft_arraydel((void ***)&f);
	print_to_bytecode(all, file, all->comm, code_size(all->comm, 0));
//	ft_printf("name - %s, int_n -%d comment - %s", all->name, all->name_i, all->comment);
//	ft_printf("\ncomm - %s\n", ((t_comm *)all->comm->content)->instr);
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
	translator(per_str = ft_strsplit(file, '\n'), 0, av[ac - 1], 0);
	free(file);
	// fd = 0;
	// while (per_str[fd])
	// 	ft_printf("%s\n", per_str[fd++]);
	// return (0);
}
