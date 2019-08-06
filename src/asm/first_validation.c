/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_vakudation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:04:16 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/05 15:04:45 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		to_ignore(char *str, int x)
{
	while (str[x] == '\t' || str[x] == ' ')
		x++;
	if (str[x] == '#' || str[x] == '\0')
		return (1);
	return (0);
}

void	ft_write_it(t_as **all, int *y, char **f, int x)
{
	while (f[*y][x])
	{
		if (f[*y][x] == '"' && to_ignore(f[*y] + x + 1, 0))
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
		if ((*all)->name_i > PROG_NAME_LENGTH || (*all)->com_i > COMMENT_LENGTH || f[*y][x] == '"')
		{
		//	ft_printf("name - %d , com - %d name - %s", (*all)->name_i, (*all)->com_i, (*all)->name);
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
	if (ft_strstr(f[*y], NAME_CMD_STRING) == f[*y] + x && !(*all)->read && !(*all)->name[0])
	{
		(*all)->read = 'n';
		x += 5;
	}
	if (ft_strstr(f[*y], COMMENT_CMD_STRING) == f[*y] + x && !(*all)->read && !(*all)->comment[0])
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
//	ft_printf("%s - str, flag - %d\n", str, flag);
	while (str[x] == '\t' || str[x] == ' ')
		x++;
	if (str[x] == COMMENT_CHAR || str[x] == '\0')
		return ;
	if (!((ft_strstr(str, NAME_CMD_STRING) && !(*all)->name[0]) || 
	(ft_strstr(str, COMMENT_CMD_STRING) && !(*all)->comment[0]) || (*all)->read))
		flag = 1;
	while (counter < 16 && !(*all)->read && (*all)->comment[0] && (*all)->name[0])
	{
		if (ft_strstr(str, op_tab[counter].op_name) == str + x)
			flag = 0;
		counter++;
	}
	if (flag == 1)
	{
		while (str[x] && ft_strindex(LABEL_CHARS, str[x]) != -1)
			x++;
	//	ft_printf("%s - str, flag - %d sym - %c\n", str, flag, str[x]);
		if (str[x] == ':' && !(*all)->read && (*all)->comment[0] && (*all)->name[0])
			flag = 0;
	}
	if (flag != 1)
		return ;
	ft_arraydel((void ***)&f);
	free(*all);
	exit(0);
}
