/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:19:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/04 19:49:14 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	validate_input(char *input, ssize_t ret)
{
	if (ret < 2195)
		return (0);
	ft_printf("%zu\n", ret);
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
		if (!(validate_input(node->content, ret)))
		{
			ft_printf("%s\n", av[i]);
			core->exit(core, INPUT_ERR, 2);
		}
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
