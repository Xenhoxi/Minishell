/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:37:12 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/18 16:18:36 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	last_exit_code(t_list *lst)
{
	t_content	*content;

	content = NULL;
	if (!lst)
		g_mini_sig = 0;
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
			g_mini_sig = content->exit_code;
		lst = lst->next;
	}
}

void	prompt(t_data *big_data)
{
	char	*input;

	input = NULL;
	ft_printf("Au debut de minishell\n");
	ft_signal();
	while (1)
	{
		input = readline(big_data->read_name);
		if (is_ctrl_d(big_data, input))
			break ;
		else if (strncmp(input, "", ft_strlen(input)) != 0)
			use_prompt(big_data, input);
	}
}

void	use_prompt(t_data *big_data, char *input)
{
	big_data->input = input;
	add_history(input);
	if (!is_quotes_open(input))
	{
		parsing(big_data);
		if (!big_data->syntax_error)
			exec(big_data);
		last_exit_code(big_data->lst_parsing->first);
		big_data->input = NULL;
		if (big_data->syntax_error)
			big_data->syntax_error = 0;
		input = NULL;
		free(input);
	}
}
