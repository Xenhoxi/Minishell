/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 01:22:34 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/07 13:46:56 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_here(t_list **lst, t_list *node_to_delete)
{
	if (!lst || !*lst || !node_to_delete)
		return ;
	if (node_to_delete->prev)
		node_to_delete->prev->next = node_to_delete->next;
	else
		*lst = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = node_to_delete->prev;
	else
		*lst = node_to_delete->prev;
	free(node_to_delete);
}

// t_list	*ft_lstdel_here(t_list **lst, t_list *node_to_delete)
// {
// 	if (!lst || !*lst || !node_to_delete)
// 		return (NULL);
// 	if (node_to_delete->prev)
// 		if (node_to_delete->next)
// 			node_to_delete->prev->next = node_to_delete->next;
// 	if (node_to_delete->prev)
// 		if (!node_to_delete->next)
// 			node_to_delete->prev->next = NULL;
// 	if (!node_to_delete->prev)
// 		if (node_to_delete->next)
// 			*lst = node_to_delete->next;
// 	if (!node_to_delete->prev)
// 		if (!node_to_delete->next)
// 			*lst = NULL;
// 	return (*lst);
// }
