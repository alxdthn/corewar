/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:45:02 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/05 18:51:19 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	puterr(const char *file, const char *error)
{
	ft_putstr_fd("Error: File ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(error, 2);
	return (0);
}

static int	validate_input(const char *input,
const ssize_t size, const char *file)
{
	int		bot_size;

	bot_size = mem_rev(*((int *)input + CODE_SIZE_OFSET));
	if (size < EXEC_CODE_OFSET)
		return (puterr(file, " is too small to be a champion"));
	if (mem_rev(((int *)input)[0]) != COREWAR_EXEC_MAGIC)
		return (puterr(file, " has an invalid header"));
	if (bot_size != size - EXEC_CODE_OFSET)
	{
		return (puterr(file,
		" has a code size that differ from what its header says"));
	}
	return (1);
}

static void	fd_error_exit(t_core *core, const char *file)
{
	ft_putstr_fd("Can't read source file ", 2);
	ft_printf("%s\n", file);
	cw_clear_exit(core, NULL, 2);
}

void		read_input(t_core *core, const int ac, const char **av)
{
	int		fd;
	int		i;
	t_list	*node;
	ssize_t	ret;

	i = 0;
	if (ac < 2)
		cw_clear_exit(core, USAGE, 1);
	else if (ac - 1 > MAX_PLAYERS)
		cw_clear_exit(core, "Too many champions", 1);
	while (++i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) < 3)
			fd_error_exit(core, av[i]);
		if (!(node = ft_lstnew(NULL, 0))
		|| (ret = ft_read_to_str(fd, (char **)&node->content, 10)) < 0)
			cw_clear_exit(core, MEM_ERROR, 2);
		if (!(validate_input(node->content, ret, av[i])))
			cw_clear_exit(core, NULL, 2);
		node->content_size = ret;
		ft_lstadd(&core->input, node);
	}
	core->war_count = i - 1;
}
