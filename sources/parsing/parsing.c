/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:23:51 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/30 14:26:28 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*setup_data(char **env)
{
	t_data	*big_data;

	big_data = malloc(sizeof(t_data));
	big_data->read_name = "Minishell-1.0$ ";
	big_data->path = ft_split(getenv("PATH"), ':');
	big_data->env = env;
	big_data->error = 0;
	big_data->input = NULL;
	big_data->lst_parsing = NULL;
	big_data->lst_cmds = NULL;
	return (big_data);
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

char	**array_join_at_index(char **array, char **array_to_join, int index)
{
	char	**new_array;
	int		i;
	int		u;
	int		j;
	int		size_total;

	i = 0;
	u = 0;
	j = 0;
	if (!array_to_join)
		return (array);
	size_total = ft_arraylen(array) + ft_arraylen(array_to_join);
	new_array = malloc(sizeof(char *) * (size_total + 1));
	while (i < size_total)
	{
		if (i == index)
			while (array_to_join[u])
				new_array[i++] = array_to_join[u++];
		else
			new_array[i++] = array[j];
		j++;
	}
	new_array[i] = NULL;
	return (new_array);
}

/*
	- Creation de la liste chaine
		- Split de l'input sur les whites_spaces()
		- Split du split precedent sur les operateur
	- Attribution de chaques mots a sa fonction via link_settings()
	(Commandes, arguments, flag).
*/
void	parsing(t_data *big_data)
{
	char		**array_split;
	char		**array_fou;
	int			i;

	i = 0;
	big_data->lst_parsing = create_data_lst();
	array_split = ft_split_fou(big_data->input);
	while (array_split[i])
	{
		array_fou = ft_split_keep_char(array_split[i]);
		array_split = array_join_at_index(array_split, array_fou, i);
		i += ft_arraylen(array_fou);
	}
	i = 0;
	while (array_split[i])
	{
		ft_lstadd_back(&big_data->lst_parsing->first,
			ft_lstnew(create_content(array_split[i], i)));
		i++;
	}
	link_settings(big_data);
	// create_lst_cmds(big_data);
}

t_content	*create_content(char *word, int i)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	if (!content)
		return (NULL);
	content->word = word;
	content->index = i;
	content->cmd_index = -1;
	content->type = NONE;
	return (content);
}

t_data_lst	*create_data_lst(void)
{
	t_data_lst	*new_data_lst;

	new_data_lst = malloc(sizeof(t_data_lst));
	if (!new_data_lst)
		return (NULL);
	new_data_lst->first = NULL;
	new_data_lst->last = NULL;
	new_data_lst->num_link = 0;
	return (new_data_lst);
}
