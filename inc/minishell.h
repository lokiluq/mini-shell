/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:51:52 by cbaey             #+#    #+#             */
/*   Updated: 2024/10/02 16:49:39 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PROMPT "\e[33mMinishell👽$ \e[0m"

extern int				g_spot;
typedef enum e_token_type
{
	WORD,
	SQUOTE,
	DQUOTE,
	IN,
	TRUNCATE,
	APPEND,
	HEREDOC,
	PIPE,
	ENV
}						t_token_type;

typedef struct s_env
{
	struct s_env		*next;
	char				*variable;
	char				*value;
}						t_env;

typedef struct s_word_type
{
	char				*str;
	int					type;
	int					str_len;
	struct s_word_type	*next;
}						t_word_type;

typedef struct s_token
{
	struct s_token		*next;
	t_word_type			*word;
	int					type;
}						t_token;

typedef struct s_child_data
{
	char				**args;
	t_token				*redirection_node;
	int					in_fd;
	int					out_fd;
}						t_child_data;

typedef struct s_params
{
	t_env				*env_list;
	t_token				*token_list;
	t_child_data		*data;
	int					exit_code;
	int					no_of_commands;
	char				*read_line;
}						t_params;

// PARSING
// command.c

void					command_prompt(char *prompt, t_params *params,
							char *line, struct sigaction sa);
bool					parse_all(t_params *params, char *line);

// env_word_checking.c

void					check_env_in_word(t_token **head, t_env *env,
							int exit_code);
void					move_token_ptr(t_token **head, t_token **current,
							t_token *prev);
void					insertion_of_sublist(t_word_type **head, t_env *env,
							int exit_code);
void					delete_and_insert(t_word_type **head,
							t_word_type *new_head, t_word_type **current,
							t_word_type **prev);
bool					expansion_of_dollar_sign(char *str, t_word_type **head,
							t_env *head_env, int exit_code);

// env_word_checking_utils.c

bool					expansion_of_dollar_sign_2(t_word_type **head,
							t_env *head_env, int exit_code, char **ptrs);
int						find_dollar_sign(t_word_type **head, char *pointer,
							char **tmp, char *start);
void					expand_env(char **tmp, t_word_type **head,
							t_env *head_env, int exit_code);
void					create_word_token(int i, t_word_type **head, char *str);
char					*env_validation(char *str, t_env *head, int exit_code,
							char *tmp);

// flattening.c

void					flatten_word_list(t_token **head);
char					*entire_word_buffer(t_word_type *word_node);
int						length_of_entire_word(t_word_type *word_node);

// parsing.c

void					parsing(t_token **head, char *str);
void					parsing_2(t_token **head, char **str, bool *first_word);
void					unquoted_str(char **str, t_token **head,
							bool *first_word);
void					find_quote(t_token **head, char **str, bool *first_word,
							char quote);

// syntax_checking.c

bool					syntax_check(t_token *head);

// UTILS
// init_env_list.c

t_env					*init_env_list(char **env);
t_env					*init_env_node(char *str);
void					append_env_list(t_env **head, char *env);
t_env					*find_last_env_node(t_env *head);

// init_main_list.c

t_token					*init_nodes(t_word_type *str, int type);
bool					append_list(t_token **head, t_word_type *str, int type);
t_token					*last_node(t_token *head);

// init_word_list.c

t_word_type				*create_word_node(char *str, int type);
void					append_word_list(t_word_type **head, char *str,
							int type);
t_word_type				*last_word_node(t_word_type *head);

// free.c

void					free_all(t_params *params);
void					free_data(t_params *params);
void					free_list(t_token **head);
void					free_word_list(t_word_type **head);
void					free_env_list(t_env *env_list);

// EXECUTION
int						prep_for_heredoc(t_params *params);
int						exec_heredoc(t_token **head, int idx, t_params *params);
int						pipe_counter(t_token *head);
void					assign_pointer_to_args(t_token **head, char **args);
int						count_nbr_of_args(t_token *head);
void					create_args(t_params *params);
void					test_for_redirection_args(t_params *params);
void					prep_for_redirect(t_params *params);
void					extract_redirect(t_token **head, t_token *prev, int i,
							t_params *params);
void					exec_all(t_params *params);
void					open_fd(t_params *params, int i, int *old_pipe,
							int *new_pipe);
int						open_out_fd(t_token *tmp, t_params *params, int i);
void					free_array(char **env_list);
char					**conv_env_list(t_env *env);
void					find_command_path(t_params *params, int i);
t_env					*find_env_node(t_env *list, char *str);
void					redirection(t_params *params, int i, int *old_pipe,
							int *new_pipe);
int						find_built_in(char *str);
void					env_handler(t_params *params, int i);
void					pwd_handler(t_params *params, int i);
char					*echo_utils(char *str, char *c);
void					echo_handler(t_params *params, int i);
void					export_handler(t_params *params, int i);
void					cd_handler(t_params *params, int i);
int						is_valid_var(char *var);
void					exec_builtin(t_params *params, int i, int built_idx);
void					unset_handler(t_params *params, int i);
t_env					*prev_env_node(t_env *list, t_env *node);
void					error_messages(int i, char *dir, char *itmatters);
void					exit_handler(t_params *params, int i);
int						is_it_number(char *str);
bool					parent_process(t_params *params, int *pipe);
void					child_process(t_params *params, int i, int *old_pipe,
							int *new_pipe);
void					pipe_handling(t_params *params, int i, int *old_pipe,
							int *new_pipe);

#endif
