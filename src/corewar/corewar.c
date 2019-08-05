/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/04 22:17:49 by nalexand         ###   ########.fr       */
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

static int	mem_rev(int mem)
{
	return ((mem & 0x000000FF) << 24
	| (mem & 0x0000FF00) << 8
	| (mem & 0x00FF0000) >> 8
	| (mem & 0xFF000000) >> 24);
}

static int	validate_input(const char *input, const ssize_t size, const char *file)
{
	int		bot_size;

	ft_printf("size: %zu\n", size);
	ft_printf("magic: %#.8x\n", mem_rev(((int *)input)[0]));
	ft_printf("name: %s\n", input + 4);
	bot_size = mem_rev(((int *)input)[34]);
	ft_printf("bot_size: %d\n ", bot_size);
	if (size < 2192)
		return (puterr(file, " is too small to be a champion"));
	if (mem_rev(((int *)input)[0]) != COREWAR_EXEC_MAGIC)
		return (puterr(file, " has an invalid header"));
	if (bot_size != size - 2192)
		return (puterr(file, " has a code size that differ from what its header says"));
	return (1);
}

static void	read_input(t_core *core, const int ac, const char **av)
{
	int		fd;
	int		i;
	t_list	*node;
	ssize_t	ret;

	i = 0;
	while (++i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) < 3)
		{
			ft_printf("%s\n", av[i]);
			core->exit(core, OPEN_ERR, 2);
		}
		if (!(node = ft_lstnew(NULL, 0))
		|| (ret = ft_read_to_str(fd, (char **)&node->content, 10)) < 0)
			core->exit(core, MEM_ERROR, 2);
		print_memory(node->content, ret);
		if (!(validate_input(node->content, ret, av[i])))
			core->exit(core, NULL, 2);
		node->content_size = ret;
		ft_lstadd(&core->input, node);
	}
}

int		main(int ac, char **av)
{
	t_core	core;

	ft_bzero(&core, sizeof(t_core));
	core.exit = &cw_clear_exit;
	read_input(&core, (const int)ac, (const char **)av);
	print_input(core.input);
	//print_map(core.map);
	ft_printf("COREWAAAR!!!\n");
	return (0);
}
