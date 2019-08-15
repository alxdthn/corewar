/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:25:02 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/15 23:14:26 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	colorize_mem(t_core *core, int pos, int color)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		core->visual.attrs[pos].light = 500;
		core->visual.attrs[pos++].index = color;
		if (pos >= MEM_SIZE)
			pos = 0;
		i++;
	}
}
