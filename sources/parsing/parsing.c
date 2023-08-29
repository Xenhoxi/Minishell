/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:23:51 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/29 15:47:50 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*setup_data(char **env)
{
	t_data	*big_data;

	(void) env;
	big_data = malloc(sizeof(t_data));
	big_data->read_name = "Minishell >> ";
	big_data->path = ft_split(getenv("PATH"), ':');
	big_data->error = 0;
	big_data->input = NULL;
	big_data->lst_parsing = NULL;
	big_data->lst_cmds = NULL;
	return (big_data);
}

// int	ft_arraylen(char **array)
// {
// 	int	i;

// 	i = 0;
// 	if (!array)
// 		return (0);
// 	while (array[i])
// 		i++;
// 	return (i);
// }

// char	**array_join_at_index(char **array, char **array_to_join, int index)
// {
// 	char	**new_array;
// 	int		i;
// 	int		u;
// 	int		j;
// 	int		size_total;

// 	i = 0;
// 	u = 0;
// 	j = 0;
// 	if (!array_to_join)
// 		return (array);
// 	size_total = ft_arraylen(array) + ft_arraylen(array_to_join);
// 	new_array = malloc(sizeof(char *) * (size_total));
// 	while (i < size_total)
// 	{
// 		if (i == index)
// 		{
// 			while (array_to_join[u])
// 			{
// 				new_array[i] = array_to_join[u];
// 				i++;
// 				u++;
// 			}
// 			j++;
// 		}
// 		else
// 		{
// 			new_array[i] = array[j];
// 			i++;
// 			j++;
// 		}
// 	}
// 	new_array[i] = NULL;
// 	return (new_array);
// }

int	is_operator_in_node(t_list *lst)
{
	int			i;
	t_content	*content;

	i = -1;
	content = (t_content *)lst->content;
	while (content->word[++i])
		if (is_operator(content->word[i]) && !between_quotes(content->word, i))
			return (1);
	return (0);
}

void	split_operator(t_list *lst)
{
	char		**array_split;
	t_content	*content;
	t_list		*initial_node;
	int			i;

	while (lst)
	{
		content = (t_content *)lst->content;
		if (is_operator_in_node(lst))
		{
			array_split = ft_split_keep_char(content->word);
			initial_node = lst;
			i = -1;
			while (array_split[++i])
			{
				ft_lstadd_here(&lst, ft_lstnew(create_content(array_split[i])));
				lst = lst->next;
			}
			ft_lstdel_here(&lst, initial_node);
		}
		lst = lst->next;
	}
}

/*
	- Creation de la liste chaine
	- Attribution de chaques mots a sa fonction
	(Commandes, arguments, flag).
*/
void	parsing(t_data *big_data)
{
	char	**array_split;
	int		i;

	i = 0;
	big_data->lst_parsing = create_data_lst();
	array_split = ft_split_fou(big_data->input);
	while (array_split[i])
	{
		ft_lstadd_back(&big_data->lst_parsing->first,
			ft_lstnew(create_content(array_split[i])));
		i++;
	}
	split_operator(big_data->lst_parsing->first);
	ft_printf("-------------\n");
	link_settings(big_data); // <- ICI CRASH
}

t_content	*create_content(char *word)
{
	t_content	*content;

	if (!word)
		return (NULL);
	content = malloc(sizeof(t_content));
	if (!content)
		return (NULL);
	content->word = word;
	content->index = -1;
	content->type = NONE;
	content->is_expand = 0;
	return (content);
}

t_data_lst	*create_data_lst(void)
{
	t_data_lst	*new_data_lst;

	new_data_lst = malloc(sizeof(t_data_lst));
	new_data_lst->first = NULL;
	new_data_lst->last = NULL;
	new_data_lst->num_link = 0;
	return (new_data_lst);
}

void	print_lst_parsing(t_list *lst_parsing)
{
	t_content	*content;

	if (!lst_parsing)
		return ;
	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		ft_printf("%s", content->word);
		if (content->type == PIPE)
			ft_printf("\tPipe");
		else if (content->type == OPERATOR)
			ft_printf("\tOperator");
		else if (content->type == REDIR_O)
			ft_printf("\tRedir out");
		else if (content->type == REDIR_I)
			ft_printf("\tRedir in");
		else if (content->type == HEREDOC)
			ft_printf("\tHeredoc");
		else if (content->type == APPEND)
			ft_printf("\tAppend");
		else if (content->type == CMD)
			ft_printf("\tCmd");
		else if (content->type == FD)
			ft_printf("\tFile");
		ft_printf("\n");
		lst_parsing = lst_parsing->next;
	}
}
