/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:21:28 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/01 00:09:59 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_lst_cmds(t_data *big_data)
{
	// t_list		*lst_parsing_f;
	// t_list		*lst_cmds_f;

	big_data->lst_cmds = create_data_lst();
	// lst_parsing_f = big_data->lst_parsing->first;
	// lst_cmds_f = big_data->lst_cmds->first;
	setup_lst_cmds(big_data, big_data->lst_parsing->first);
	print_lst_cmds(big_data->lst_cmds);
}

char	**array_join(char **array, char *line)
{
	int		i;
	char	**new_array;
	int		len;

	i = 0;
	if (!array)
		i = 0;
	else
		while (array[i])
			i++;
	len = i;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = line;
	new_array[++i] = NULL;
	free(array);
	return (new_array);
}

void	ft_print_tab(char **array)
{
	int	i;

	i = -1;
	if (!array)
	{
		printf("array[0] = (NULL)\n");
		return ;
	}
	while (array[++i])
		printf("array[%d] = %s\n", i, array[i]);
}

void	setup_lst_cmds(t_data *big_data, t_list *lst)
{
	t_cmds		*cmds_new;

	while (lst)
	{
		cmds_new = create_cmds(NULL, ((t_content *)lst->content)->type);
		while (((t_content *)lst->content)->type != PIPE && lst)
		{
			if (((t_content *)lst->content)->type == CMD)
			{
				((t_cmds *)cmds_new)->cmd = array_join(((t_cmds *)cmds_new)->cmd, ((t_content *)lst->content)->word);
				// ft_lstdel_here(&lst, lst);
				lst = lst->next;
				if (lst == NULL)
				{
					ft_lstadd_back(&big_data->lst_cmds->first, ft_lstnew(cmds_new));
					break ;
				}
			}
			else
				lst = lst->next;
		}
		if (lst)
		{
			ft_lstadd_back(&big_data->lst_cmds->first, ft_lstnew(cmds_new));
			lst = lst->next;
		}
	}
}

t_cmds	*create_cmds(char *word, t_type type)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->type = type;
	cmds->cmd = array_join(NULL, word);
	cmds->infile = -1;
	cmds->outfile = -1;
	return (cmds);
}

void	define_index_cmds(t_list *lst)
{
	t_content	*content;
	int			i;

	i = 0;
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
		{
			content->cmd_index = i;
			lst = lst->next;
		}
		else if (content->type == PIPE)
		{
			i++;
			while (content->type == PIPE)
			{
				content->cmd_index = i;
				lst = lst->next;
				content = (t_content *)lst->content;
			}
		}
	}
}

void	print_lst_cmds(t_data_lst *lst_cmds)
{
	t_list	*lst;
	t_cmds	*cmds_content;

	lst = lst_cmds->first;
	while (lst)
	{
		cmds_content = (t_cmds *)lst->content;
		ft_print_tab(cmds_content->cmd);
		if (lst->next)
			ft_printf("|\n");
		lst = lst->next;
	}
}
