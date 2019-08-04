/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_read_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:04:35 by unicolle          #+#    #+#             */
/*   Updated: 2019/08/04 17:17:42 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char				*list_to_str(t_list **lst, size_t size)
{
	char	*res;
	t_list	*tmp;

	res = NULL;
	if (!size || !(res = (char *)malloc(sizeof(char) * (size + 1))))
	{
		ft_lstdel(lst);
		return (NULL);
	}
	res[size] = '\0';
	while (size)
	{
		size -= (*lst)->size;
		ft_memcpy(res + size, (*lst)->data, (*lst)->size);
		tmp = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
	return (res);
}

char				*fast_read_file(int fd)
{
	int		ret;
	char	buf[BUFF_SIZE];
	size_t	size;
	t_list	*lst;
	t_list	*elem;

	size = 0;
	lst = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!(elem = ft_lstnew(buf, (size_t)ret)))
		{
			ft_lstdel(&lst);
			return (NULL);
		}
		ft_lstadd(&lst, elem);
		size += (size_t)ret;
	}
	return (list_to_str(&lst, size));
}
