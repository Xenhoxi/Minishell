/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:48:53 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 16:07:10 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_content *content, t_data *big_data)
{
	char	*pwd;
	char	*path;

	pwd = NULL;
	path = NULL;
	if (content->cmd[1] != NULL)
	{
		pwd = getcwd(pwd, CWD_SIZE);
		path = ft_strjoin(pwd, "/");
		path = ft_strjoin(path, content->cmd[1]);
	}
	else
	{
		chdir(big_data->root_path);
		return ;
	}
	if (opendir(path) == NULL)
	{
		ft_printf("minishell: cd: %s: ", content->cmd[1]);
		perror("");
	}
	else
		chdir(path);
}
