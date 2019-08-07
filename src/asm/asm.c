/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:10:58 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 22:14:06 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	delete_asm_all(t_as **all, char **file, char ***f)
{
	if (f && *f)
		ft_arraydel((void ***)f);
	if (file && *file) 
		free(*file);
	if (all && *all)
	{
		// del_com(all, (*all)->comm);
		// del_labels(all, (*all)->labels);
		free(*all);
	}
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
	//	ft_printf("%s\n", f[y]);
		if (ft_strstr(f[y], NAME_CMD_STRING) || ft_strstr(f[y], COMMENT_CMD_STRING) || all->read)
			add_names(&all, &y, f, 0);
		else if (add_label(&all, f, f[y], y) && !to_ignore(f[y], 0))
			add_command(&all, 0, f, f[y]);
		y++;
	}
	label_to_nbr(&all, all->labels, all->comm, 0);
//	ft_arraydel((void ***)&f);
	print_to_bytecode(all, file, all->comm, code_size(all->comm, 0));
	//delete_asm_all(&all, &file, &f);
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
	close(fd);
	// fd = 0;
	// while (per_str[fd])
	// 	ft_printf("%s\n", per_str[fd++]);
	// return (0);
}
