/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:53:34 by wbelfatm          #+#    #+#             */
/*   Updated: 2025/01/10 15:19:52 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <termios.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <limits.h>
# include "./libft/libft.h"

# define MAX_CWD 1024
# define CD_HOME 0
# define CD_OLDPWD 1
# define CD_RROR  "minishell: cd: getcwd: cannot access parent directories: "

typedef enum e_type
{
	TOKEN_EXPR,
	TOKEN_EXEC,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SPACE,
	TOKEN_BRKT_OPEN,
	TOKEN_BRKT_CLOSE,
	TOKEN_D_Q,
	TOKEN_S_Q,
	TOKEN_DOLLAR,
}	t_type;

typedef struct s_content
{
	t_type				node_type;
	char				*str;
	struct s_content	*next;
}	t_content;

typedef struct s_lex
{
	t_type			node_type;
	char			*content;
	struct s_lex	*next;
}	t_lex;

typedef struct s_tree
{
	t_type			node_type;
	struct s_tree	*left;
	struct s_tree	*right;
	char			**command;
	char			**command_tmp;
	t_content		*content_list;
	char			*filename;
	char			*buffer;
	bool			expand_heredoc;
	bool			heredoc_read;
	int				heredoc_order;
}	t_tree;

typedef struct s_env
{
	char			*name;
	char			*value;
	char			*full;
	struct s_env	*next;
}	t_env;

typedef struct s_set
{
	char			*name;
	char			*value;
	struct s_set	*next;
}	t_set;

typedef struct s_config
{
	int			i;
	char		*line;
	t_lex		*tokens_list;
	t_tree		*tree;
	t_tree		*tmp_tree;
	char		*tmp_line;
	t_lex		*tmp_list;
	int			last_status;
	char		**env;
	t_env		*env_list;
	int			std_out;
	int			std_in;
	bool		fail;
	bool		env_exists;
	int			last_heredoc;
	int			heredocs_to_execute;
	int			heredocs_executed;
	bool		command_in;
	char		*error_msg;
	int			flag;
	char		*tmp;
	bool		content_quoted;
}	t_config;

// tree creation
t_tree		*create_tree_node(t_type type, t_config *config);
t_tree		*construct_cmdline(t_tree *left, t_tree *right,
				t_type type, t_config *config);
t_tree		*construct_pipe(t_tree *left, t_tree *right, t_config *config);
t_tree		*construct_command(t_tree *left, t_tree *right, t_config *config);
t_tree		*construct_redir(int token, t_lex **tokens_list,
				t_tree *tree, t_config *config);
// parse
t_tree		*parse_cmdline(t_config *config);
t_tree		*parse_pipe(t_config *config);
t_tree		*parse_command(t_config *config);
t_tree		*parse_exec(t_config *config);
t_tree		*parse_cmdlist(t_config *config);
t_tree		*parse_redir(t_config *config, t_tree *tree);
bool		is_redirection(t_type type);

// execute
int			execute_cmdline(t_config *config);
void		execute_redir(t_config *config);
int			execute_condition(t_config *config);
int			execute_pipe(t_config *config);
int			execute_command(t_config *config);
int			execute_builtin(t_config *config);
int			execute_single(t_config *config);
int			execute_subshell(t_config *config, t_tree *tree);
void		fork_execute(t_config *config, t_tree *tree);
void		traverse_heredoc(t_tree *tree, t_config *config, int order);
int			execute_redir_hd(t_config *config, t_tree *tree);
// lexer
t_lex		*lex_line(char **line);
// eval
t_content	*eval_content(char *content);
char		*eval_quotes(char **line, t_type *type, char *tokens);
char		*eval_symbols(char **line, t_type *type);
char		*eval_string(char **line, t_type *type, char *tokens);
char		*append_char(char *str, char c);
char		*get_content(char **line, t_type *type);
void		append_node(t_lex **list, char **line);
void		assign_type(char *res, t_type *type);
char		*eval_next_string(char *res, char **line,
				t_type *type, char *tokens);
char		*eval_next_quotes(char **line, char *res,
				t_type *type, char *tokens);
char		*advance_append(char *str, char *res, int *i);

// utils
char		**get_command(t_config *config, t_content *content_list, char op);
void		print_tree(t_tree *tree, int level);
bool		look_ahead(char **start, char *chars, int and_or);
char		*find_path(char *command, char *paths);
char		*expand_variables(char *line, t_config *config,
				bool is_quoted, bool next_quoted);
int			find_paths_index(char **env);
bool		check_match(char *pattern, char *word);
void		expand_command(char **command, t_config *config, bool is_quoted);
void		append_content_node(t_content **content, char *str, t_type type);
t_content	*get_content_list(t_config *config, char op);
void		my_putstr(char *str);
bool		is_executable(t_lex *content_list);
char		*join_array(char **arr, bool free_arr);
void		fail_config(t_config *config);
void		put_error(char *s1, char *s2, char *s3);
bool		check_next_quoted(t_content *content_list);
bool		check_fail(t_lex **tokens_list, t_config *config);
char		*get_heredoc_command(t_content *content_list, char *command);
char		*guard_command(char *command, t_content *content_list);
void		free_list_null(t_env **list);
char		*trim_free(char *str);

// redir utils
int			redirect_reset(t_config *config);

// execute utils
int			get_exit_code(char *str, char *command);
char		*get_command_path(t_config *config, char *command);

// memory management
int			add_mem(t_config *config, void *mem);
void		free_garbage(t_config *config);
void		free_lex_list(t_lex **list);
void		free_content_list(t_content *list);
void		free_array(char **arr);
void		free_tree(t_tree *tree);
void		free_env_list(t_env *env);

//=======================Built-ins===============================//
int			ft_cd(char *args, char **env, bool *flag);
int			ft_echo(char *str);
int			ft_env(char **env, t_config *config);
int			ft_export(t_config *config, char **args);
int			ft_pwd(t_config *config);
int			ft_unset(t_config *config, char **args);
t_env		*get_env_list(t_config *config);
// built-in utils
int			update_oldpwd_pwd(char **env, const char *oldpwd, const char *pwd);
void		ft_update(char ***env);
int			ft_update_faile(char ***env, char *arg);
char		*ft_getenv(char **env, const char *name);
void		ft_setenv(t_config *config, char *name, char *value);
void		ft_unsetenv(t_config *config, const char *name);
bool		is_builtin(char *command);
char		**list_to_array(t_env *env);
void		print_cd_error(void);
void		*ft_free(void *ptr);
void		append_env_node(t_env **list, char *variable);
bool		valid_name(char *name, char *full);
bool		valid_name_unset(char *name);
//=======================Expanding===============================//
char		*expand_star(char *word, int *count);
char		*get_variable_value(t_config *config, char *word,
				int i, bool next_quoted);
char		*expand_word(char *word, int count, t_config *config,
				bool next_quoted);
bool		check_match(char *pattern, char *word);
char		*expand_dollar(char *line, t_config *config,
				bool is_quoted, bool next_quoted);
char		*expand_special(t_config *config, char *word, bool next_quoted);
char		*expand_point_exit(t_config *config,
				char *word, int i, bool next_quoted);
char		*expand_exit_status(t_config *config, char *word, bool next_quoted);
char		*expand_point(t_config *config, char *word, bool next_quoted);
// expand utils
bool		ft_issymbol(char c);
char		*check_and_join(char *word, int *count, DIR *dir);
bool		is_only_char(char *str, char c);
char		*append_special(char **split_word);
// append
char		**append_command(char **commands, char *command, t_config *config);
// insert
char		**insert_array(char **first, char **second, int *i);
// remove
char		*remove_char(char *str, char c);
// env
void		update_env(t_config *config);
char		*get_env_var(char *name, t_config *config);
void		add_set(t_config *config, char **args);
// extract utils
char		*get_normal_command(t_content *content_list,
				t_config *config, char *command, char op);
char		**handle_finish(t_config *config, char **res, char op);
char		**finish_command(char **res, char op);
char		**handle_star(char **res, int *i, char op);
// match
bool		check_word_finished(char *pattern, int i);
bool		advance_pattern(char *pattern, int *i, bool *in_quotes);
bool		set_inquotes(int *i, bool *in_quotes);
//=======================Signals===============================//
void		sig_int(int code);
void		*ft_free(void *ptr);
void		handleint(int code);
void		reset_terminal(void);
void		sig_herdoc(int code);

//=======================Syntax===============================//
typedef struct s_token
{
	enum e_type		type;
	bool			q_flag;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_tok;

extern long	g_here_flag[2];

bool		ft_syntax(const char *line, int *heredoc_value,
				char **error_to_print);
void		ft_update(char ***env);
bool		check_syn(char *line);
bool		check_parenthese(t_tok *head, int *heredoc);
bool		check_start_end_tokens(t_tok *head, int *heredoc);
bool		check_redir_before_bracket(t_tok *head, int *heredoc);
bool		closed_quotes(char *str);
bool		closed_parentheses(t_tok *head, int *heredoc);
char		*ft_strtok(char *str, const char *delim, bool *flag);
void		my_free_list(t_tok *tokens);
t_tok		*syn_tokenize(char *cmdline);
bool		check_redir_in_out(t_tok *head, int *heredoc);
bool		check_tokens(t_tok *head, int *heredoc);
char		**allocate_environment(char **real_env);

// main utils
void		check_env(t_config *config);
void		init_config(t_config *config, char **env);
void		reset_config(t_config *config);
int			free_null(char **str);
void		print_error(t_config *config);
void		handle_syntax_error(t_config *config);
void		check_break(t_config *config, int op);
void		check_line(t_config *config, char *line);
void		ft_void(int argc, char **argv);
int			set_lex(t_config *config);
int			display_free(t_config *config);
void		finish_execution(t_config *config);
int			parse_init(t_config *config);
int			parse_fail(t_config *config);
int			execute(t_config *config);

#endif