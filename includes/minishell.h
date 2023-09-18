/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:43:06 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/18 18:42:24 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

# define TRUE 1
# define FALSE 0

# define ERROR 1
# define ALL_G 0

# define CWD_SIZE 64

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
	int			exit_code;
	pid_t		child;
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
	char		*root_path;
	int			syntax_error;
	t_data_lst	*lst_parsing;
}	t_data;

/*---------*/
/*  SETUP  */
/*---------*/

// prompt.c
void		prompt(t_data *big_data);
void		use_prompt(t_data *big_data, char *input);

/*---------*/
/*  SIGNAL */
/*---------*/

// signal.c
void		ft_signal(void);
void		ft_signal_in_fork(void);
void		sig_handler(int sig, siginfo_t *info, void *context);
void		sig_handler_in_fork(int sig, siginfo_t *info, void *context);
int			is_ctrl_d(t_data *big_data, char *input);

/*---------*/
/* PARSING */
/*---------*/

// parsing.c
void		print_lst_parsing(t_list *lst_parsing);
char		**array_join_at_index(char **array, char **a_join, int index);
t_data_lst	*create_data_lst(void);
t_content	*create_content(char *word, int i);
t_data		*setup_data(char **env);
void		parsing(t_data *big_data);

// parsing_utils.c
char		*ft_strjoin_char(char *s1, char s2);
int			is_quoted(char *input);
void		print_lst_parsing(t_list *lst_parsing);

// parsing_utils_2.c
int			ft_arraylen(char **array);
char		**array_dup(char **array);
int			is_unmanaged_operator(t_list *lst, t_data *big_data);
t_content	*create_content(char *word, int i);
t_data_lst	*create_data_lst(void);

// parsing/parsing_atribute.c
int			is_cmds(t_content *content, t_list *prev);
void		find_separator(t_list *lst_parsing);
void		define_word(t_list *lst_parsing);
void		find_fd(t_list *lst_parsing);
void		link_settings(t_data *big_data);

// parsing/check_arg.c
int			check_arg(int argc, char **argv);
int			freeall(t_data *data, int status);

// parsing/lexing_cmds.c
void		create_lst_cmds(t_data *big_data);
void		print_lst_cmds(t_data_lst *lst_cmds);
void		define_index_cmds(t_list *lst);
void		setup_lst_cmds(t_list *lst);
char		**array_join(char **array, char *line);

// parsing/ft_split_fou.c
int			count_word(char *input);
char		*go_to_next_space(char *input);
char		*go_to_next_word(char *input);
char		**ft_split_fou(char *input);
int			is_white_space(char c);

// parsing/ft_split_fou_utils.c
int			between_quotes(char	*input, int goal);
int			len_word(char *input);
int			is_quoted_and_who(char	*input, int goal);

// ft_split_keep_char.c
char		*go_to_next_word_keep(char *input);
char		*go_to_next_operator(char *input);
int			len_word_keep(char *input);
int			count_word_keep(char *input);
char		**ft_split_keep_char(char *input);

// ft_split_keep_char_utils.c
int			is_operator(char c);
int			count_operator(char *input);

// quoting.c
char		*rm_quotes(char *word, int q1, int q2);
void		quotes_killer(t_content *content);
void		call_rm_quotes(t_list *lst_parsing);
int			find_index_from(char *str, char *q_type, int start);
int			is_quotes_open(char *input);

// ft_env.c
void		env_var_expansion(t_data *big_data, t_list *lst_parsing);
char		*cut_to_getenv(int *i, char *p1, t_content *cont, t_data *big_data);
char		*ft_getenv(t_data *big_data, char *find_env);
void		env_to_string(t_data *big_data, t_content *content);

// ft_env_utils.c
int			is_env_var(t_content *content);
int			ft_is_envchar(int c);

// parsing/heredoc_gestion.c
int			is_not_delimitor_after_heredoc(t_list *lst);
int			is_heredoc_in_lst(t_list *lst);
void		heredoc_read(t_list *lst, int i);
void		do_heredoc_things(t_list *lst);
void		heredoc_gestion(t_data *big_data);

// parsing/lexing_cmds.c
void		create_lst_cmds(t_data *big_data);
char		**array_join(char **array, char *line);
void		ft_print_tab(char **array);
void		create_cmd_in_content(t_content *cont, t_list **save, t_list *lst);
void		setup_lst_cmds(t_list *lst);

// redirection.c
int			is_not_redir_and_file(t_list *lst);
void		check_redir_files(t_data *big_data);
void		check_file_existence(t_data *big_data, t_list *lst);
void		check_perm_and_exist(t_list *lst);
void		is_fd_after_separator(t_data *big_data, t_list *lst);

// redirections_utils.c
t_list		*find_next_cmd(t_list *lst);
int			is_redir(t_content *content);
int			is_redir_in_lst(t_list *lst);

// permissions.c
void		checking_fd(int fd, t_list **current_cmd, t_content *content_next);
void		check_redir_out(t_list *lst, t_list **current_cmd);
void		check_redir_in(t_list *lst, t_list **current_cmd);
void		check_append(t_list *lst, t_list **current_cmd);

// ft_lst_remove_if.c
t_list		*ft_remove_trash(t_list *lst, t_list *to_delete);
void		ft_check_for_trash(t_list *lst);
// void		ft_list_remove_if(t_list **begin_list);
t_list		*remove_if(t_list *lst, t_list *node_to_delete);
void		node_to_del(t_data_lst *lst_parsing);

/*-----------*/
/* EXECUTION */
/*-----------*/

// pipex/pipex_main.c
void		get_cmd_path(t_data *big_data, t_content *content);
void		exec(t_data *big_data);
int			ft_count_cmds(t_data *big_data);

// pipex/pipex.c
void		create_childs(t_data *big_data);
void		pipe_it_up(t_data *big_data);
void		exec_child(t_content *cmd, t_data *big_data);
t_content	*find_prev(t_list *lst);
void		close_fd(t_content *content);

// setup_pipe.c
void		pipe_syntax_checker(t_data *big_data, t_list *lst);
void		pipe_it_up(t_data *big_data);
void		is_pipe_stuck(t_data *big_data);

/*------------*/
/*  BUILTINS  */
/*------------*/

// builtins/builtins_utils.c
void		exec_builtins(char *cmd, t_content *content, t_data *big_data);
int			is_builtin(t_content *content);

// builtins
void		ft_pwd(t_content *cont);
void		ft_cd(t_content *content, t_data *big_data);
char		*check_tilde(t_content *content, t_data *big_data);
void		ft_echo(t_content *content);
void		ft_export(t_data *big_data, t_content *cont);
void		ft_exit(t_content *content, t_data *big_data);
void		ft_unset(t_content *content, t_data *big_data);
void		ft_env(t_data *big_data, t_content *cont);

/*-----------*/
/*  FREEING  */
/*-----------*/

// freeing/free_chainlink.c
void		free_chainlink(t_data_lst *data_parsing);
char		**ft_split_keep_char(char *input);
void		ft_print_tab(char **array);
void		free_lst_content(t_data_lst *lst_parsing);

// free_utils.c
void		ft_free_array(char **array);

#endif