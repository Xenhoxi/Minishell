/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:41:51 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/16 22:27:08 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_remove_trash(t_list *lst, t_list *to_delete)
{
	t_list	*new_head;

	if (lst == NULL || to_delete == NULL)
		return (lst);
	if (lst == to_delete)
	{
		new_head = lst->next;
		if (new_head != NULL)
			new_head->prev = NULL;
		free(lst->content);
		free(lst);
		return (new_head);
	}
	if (to_delete->prev != NULL)
		to_delete->prev->next = to_delete->next;
	if (to_delete->next != NULL)
		to_delete->next->prev = to_delete->prev;
	free(to_delete->content);
	free(to_delete);
	return (lst);
}

void	ft_check_for_trash(t_list *lst)
{
	t_list		*tmp;
	t_content	*content;

	while (lst)
	{
		if (lst->content != NULL)
		{
			content = (t_content *)lst->content;
			if (content->to_delete == 1)
			{
				tmp = lst;
				lst = lst->next;
				free(tmp->content);
				tmp->content = NULL;
				lst = ft_remove_trash(lst, lst);
			}
			else
				lst = lst->next;
		}
		else
			lst = lst->next;
	}
}

// int	is_node_to_del(t_list *lst)
// {
// 	t_content	*content;

// 	while (lst)
// 	{
// 		content = (t_content *)lst->content;
// 		if (content->to_delete)
// 			return (1);
// 		lst = lst->next;
// 	}
// }

// void	ft_check_for_trash(t_list *lst)
// {
// 	while (is_node_to_del(lst))
// 	{
// 		// in_test;
// 	}
// }

void	ft_list_remove_if(t_list **begin_list)
{
	t_list	*cur;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	cur = *begin_list;
	if (((t_content *)cur->content)->to_delete == 1)
	{
		*begin_list = cur->next;
		if (cur->prev && cur->next)
		{
			cur->next->prev = cur->prev;
			cur->prev->next = cur->next;
		}
		free(cur);
		ft_list_remove_if(begin_list);
	}
	else
		ft_list_remove_if(&(*begin_list)->next);
}