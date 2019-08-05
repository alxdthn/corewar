/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_clear_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 18:01:23 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/04 18:27:24 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_clear_exit(t_core *core, const char *message, const int fd)
{
	ft_lstdel(&core->input, ft_lstclear);
	if (message)
		ft_putendl_fd(message, fd);
	if (fd == 2)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);	
}
