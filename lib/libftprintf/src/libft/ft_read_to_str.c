/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 21:48:03 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/04 17:25:03 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	list_to_str(t_list **lst, size_t size, char **str)
{
	char	*res;
	t_list	*tmp;

	res = NULL;
	if (!size || !(res = (char *)malloc(sizeof(char) * (size + 1))))
	{
		ft_lstdel(lst, ft_lstclear);
		return (-1);
	}
	res[size] = '\0';
	while (size)
	{
		size -= (*lst)->content_size;
		ft_memcpy(res + size, (*lst)->content, (*lst)->content_size);
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	return (res);
}

ssize_t		ft_read_to_str(int fd, char **str, size_t b_size)
{
	char	buf[b_size];
	ssize_t	ret;
	ssize_t	size;
	t_list	*lst;
	t_list	*elem;

	size = 0;
	lst = NULL;
	while ((ret = read(fd, buf, b_size)) > 0)
	{
		if (!(elem = ft_lstnew(buf, ret)))
		{
			ft_lstdel(&lst, ft_lstclear);
			return (-1);
		}
		ft_lstadd(&lst, elem);
		size += ret;
	}
	return (list_to_str(&lst, size, str));
}
