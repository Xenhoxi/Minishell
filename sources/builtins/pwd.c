/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:24:32 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/13 14:13:56 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	buffer[CWD_SIZE];

	if (getcwd(buffer, CWD_SIZE) == NULL)
		perror("Getcwd failed");
	else
	{
		write(1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
	}
}