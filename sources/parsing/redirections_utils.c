/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:26:29 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/26 14:44:37 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_content *content)
{
	if (content->type == REDIR_I || content->type == REDIR_O
		|| content->type == APPEND)
		return (1);
	return (0);
}

int	is_redir_in_lst(t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = ((t_content *)lst->content);
		if (is_redir(content) || content->type == HEREDOC)
			return (1);
		lst = lst->next;
	}
	return (0);
}

t_list	*find_next_cmd(t_list *lst)
{
	t_content	*content;

	if (lst)
		content = ((t_content *)lst->content);
	while (lst && content->type != PIPE)
	{
		content = ((t_content *)lst->content);
		if (content->type == CMD)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	is_fd_after_separator(t_data *big_data, t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = ((t_content *)lst->content);
		if (is_redir(content) || content->type == HEREDOC)
		{
			if (lst->next == 0)
			{
				msg_e("minishell: syntax error near unexpected token `newline'",
					NULL, "\n");
				big_data->syntax_error = 1;
				g_mini_sig = 2;
				return ;
			}
			if (((t_content *)lst->next->content)->type != FD)
				return (msg_e("minishell: syntax error near unexpected token `",
						((t_content *)lst->next->content)->word, "'\n"),
					big_data->syntax_error = 1, g_mini_sig = 2, (void)0);
		}
		lst = lst->next;
	}
}

void	check_no_cmd(t_list *lst)
{
	t_content	*content;
	t_content	*content_next;
	int			fd;

	fd = 0;
	if (!lst || !lst->next)
		return ;
	content = (t_content *)lst->content;
	content_next = (t_content *)lst->next->content;
	if (content->type != HEREDOC)
	{
		if (content->type == REDIR_I)
			fd = open(content_next->word,
					O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			fd = open(content_next->word, O_CREAT | O_TRUNC
					| O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		checking_fd(fd, NULL, content_next);
	}
	if (fd > 0)
		close(fd);
	content->to_delete = 1;
	content_next->to_delete = 1;
}
