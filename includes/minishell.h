/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:43:06 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/07 14:48:20 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define TRUE 1
# define FALSE 0

# define ERROR 1
# define ALL_G 0

int	g_mini_sig;

typedef enum s_type
{
	NONE,
	CMD,
	PIPE,
	OPERATOR,
	REDIR_I,
	REDIR_O,
	APPEND,
	HEREDOC,
	FD,
}	t_type;

// Struct contenant un maillon du parsing
typedef struct s_content
{
	char		*word;
	char		**cmd;
	char		*pathed;
	int			infile;
	int			outfile;
	int			index;
	int			fdp[2];
	int			to_delete;
	int			error;
	int			need_bro;
	t_type		type;
}	t_content;

// Struct contenant les adresses d'une liste chainée
typedef struct s_data_lst
{
	t_list		*first;
	t_list		*last;
	int			num_link;
}	t_data_lst;

// Stuct principale 
typedef struct s_data
{
	char		*read_name;
	char		**path;
	char		**env;
	char		*input;
	int			syntax_error;
	pid_t		big_bro;
	pid_t		little_bro;
	t_data_lst	*lst_parsing;
}	t_data;

//  pipex/pipex.c
void		create_childs(t_data *big_data);
void		pipe_it_up(t_data *big_data);
void		exec_big_bro(t_content *cmd, t_content *lil_bro, t_data *big_data);
void		exec_little_bro(t_content *cmd, t_data *big_data);
t_content	*get_little_bro(t_data *big_data);

// pipex/pipex_main.c
void		get_cmd_path(t_data *big_data, t_content *content);
void		exec(t_data *big_data);
int			ft_count_cmds(t_data *big_data);
// prompt/prompt.c
void		prompt(t_data *big_data);
void		use_prompt(t_data *big_data, char *input);

// prompt/signal.c
void		ft_signal(void);
void		sig_handler(int sig, siginfo_t *info, void *context);
int			is_ctrl_d(t_data *big_data, char *input);

// parsing/parsing.c
t_data_lst	*create_data_lst(void);
t_content	*create_content(char *word, int i);
t_data		*setup_data(char **env);
void		parsing(t_data *big_data);

// parsing/parsing.c
void		print_lst_parsing(t_list *lst_parsing);
int			is_quoted(char *input);
char		**array_join_at_index(char **array, char **a_join, int index);

// parsing/parsing_atribute.c
int			is_separator(t_content	*content);
int			is_flag(t_content *content);
int			is_quotes_open(char *input);
int			char_in_squotes(t_content *content, int goal);
void		link_settings(t_data *big_data);

// parsing/check_arg.c
int			check_arg(int argc, char **argv);
int			freeall(t_data *data, int status);

// parsing/lexing_cmds.c
void		create_lst_cmds(t_data *big_data);
void		print_lst_cmds(t_data_lst *lst_cmds);
void		define_index_cmds(t_list *lst);
void		setup_lst_cmds(t_data *big_data, t_list *lst);

// parsing/ft_split_fou.c
int			count_word(char *input);
int			len_word(char *input);
char		*go_to_next_space(char *input);
char		*go_to_next_word(char *input);
char		**ft_split_fou(char *input);
int			is_white_space(char c);

// parsing/ft_split_fou_utils.c
int			between_quotes(char	*input, int goal);
int			is_quoted_and_who(char	*input, int goal);

// parsing/env_var_expansion.c
int			is_env_var(t_content *content);
int			is_quotes_open(char *input);
void		change_env_var(t_list *lst_parsing);
void		env_to_string(t_data *big_data, t_content *content);
void		env_var_expansion(t_data *big_data, t_list *lst_parsing);
char		*ft_getenv(t_data *big_data, char *find_env);
char		*ft_strjoin_char(char *s1, char s2);

// parsing/quoting.c
char		*rm_quotes(char *word, int q1, int q2);
void		call_rm_quotes(t_list *lst_parsing);
int			find_index_from(char *str, char *q_type, int start);
void		quotes_killer(t_content *content);

// freeing/free_chainlink.c
void		free_chainlink(t_data_lst *data_parsing);

char		**ft_split_keep_char(char *input);
void		ft_print_tab(char **array);

// parsing/file_and_redir.c
void		check_redir_files(t_data *big_data);

// parsing/heredoc_gestion.c
void		heredoc_gestion(t_data *big_data);

void		node_to_delete(t_list *lst);
void		pipe_syntax_checker(t_data *big_data, t_list *lst);
int			is_redir(t_content *content);
void		check_perm_and_exist(t_list *lst);
void		ft_list_remove_if(t_list **begin_list);

#endif