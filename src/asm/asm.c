/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:10:58 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/04 22:59:26 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_write_it(t_as **all, int *y, char **f, int x)
{
	while (f[*y][x])
	{
		if (f[*y][x] == '"')
		{
			(*all)->read = '\0';
			break;
		}
		if ((*all)->read == 'N')
		{
			(*all)->name[(*all)->name_i] = f[*y][x];
			(*all)->name_i++;
		}
		if ((*all)->read == 'C')
		{
			(*all)->comment[(*all)->com_i] = f[*y][x];
			(*all)->com_i++;
		}
		if ((*all)->name_i > PROG_NAME_LENGTH || (*all)->com_i > COMMENT_LENGTH)
		{
			ft_printf("name - %d , com - %d name - %s", (*all)->name_i, (*all)->com_i, (*all)->name);
			exit(0);
		}
		x++;
	}
}

void	add_names(t_as **all, int *y, char **f, int x)
{
	char	*str;

	while (f[*y][x] == '\t' || f[*y][x] == ' ')
		x++;
	if (ft_strstr(f[*y], NAME_CMD_STRING) == f[*y] + x && !(*all)->read)
	{
		(*all)->read = 'n';
		x += 5;
	}
	if (ft_strstr(f[*y], COMMENT_CMD_STRING) == f[*y] + x && !(*all)->read)
	{
		(*all)->read = 'c';
		x += 8;
	}
	while (f[*y][x] == '\t' || f[*y][x] == ' ')
		x++;
	if ((*all)->read == 'n' && f[*y][x] == '"')
	{
		(*all)->read = 'N';
		x++;
	}
	if ((*all)->read == 'c' && f[*y][x] == '"')
	{
		(*all)->read = 'C';
		x++;
	}
	if ((*all)->read == 'C' || (*all)->read == 'N')
		ft_write_it(all, y, f, x);
	if ((*all)->read == 'c' || (*all)->read == 'n')
	{
		ft_printf("%c\n symbol - %c", (*all)->read, f[*y][x]);
		ft_arraydel((void ***)&f);
		free(*all);
		exit(0);
	}
}

void	check_to_valid(char *str, int x, t_as **all, char **f)
{
	int		flag;
	int		counter;

	flag = 0;
	counter = 0;
	while (str[x] == '\t' || str[x] == ' ')
		x++;
	if (str[x] == COMMENT_CHAR || str[x] == '\0')
		return ;
	if (!(ft_strstr(str, NAME_CMD_STRING) || ft_strstr(str, COMMENT_CMD_STRING) || (*all)->read))
		flag = 1;
	while (counter < 16)
	{
		if (ft_strstr(str, op_tab[counter].op_name) == str + x)
			flag = 0;
		counter++;
	}
	if (flag == 1)
	{
		while (str[x] && ft_strstr(&(str[x]), LABEL_CHARS))
			x++;
		if(str[x] == ':')
			flag = 0;
	}
	if (flag != 1)
		return ;
	ft_arraydel((void ***)&f);
	free(*all);
	exit(0);
}

int		to_ignore(char *str, int x)
{
	while (str[x] == '\t' || str[x] == ' ')
		x++;
	if (str[x] == '#' || str[x] == '\0')
		return (1);
	return (0);
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
		if (to_ignore(f[y], 0))
		{}
		else if (ft_strstr(f[y], NAME_CMD_STRING) || ft_strstr(f[y], COMMENT_CMD_STRING) || all->read)
		{
			add_names(&all, &y, f, 0);
		}
		// else
		// 	add_command(&all, y, f);
		y++;
	}
	ft_printf("name - %s, int_n -%d comment - %s", all->name, all->name_i, all->comment);
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
	if (ft_read_to_str(fd, &file, 10) == -1)
		return (0);// надо обработать, и предыдущие тоже
//	ft_printf("%s\n", file);
	translator(per_str = ft_strsplit(file, '\n'), 0, 0, 0);
	free(file);
	// fd = 0;
	// while (per_str[fd])
	// 	ft_printf("%s\n", per_str[fd++]);
	// return (0);
}
