/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:10:16 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 09:56:30 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*new_list;

	if (!lst | !del)
		return ;
	while (*lst)
	{
		new_list = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = new_list;
	}
	new_list = NULL;
}
