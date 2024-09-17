/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:56:02 by labdello          #+#    #+#             */
/*   Updated: 2024/09/20 15:38:48 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ENV_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:\
/bin:/usr/games:/usr/local/games:/snap/bin/"

# include "libft.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_entry_list
{
	char				*name;
	struct s_entry_list	*prev;
	struct s_entry_list	*next;
}				t_entry_list;

typedef struct s_env
{
	char	*path;
	char	**vars;
	char	**virtual_vars;
	int		fd_in;
	int		fd_out;
	int		last_status;
	int		s_expand;
	int		is_env;
}				t_env;

typedef struct s_word
{
	char			*content;
	int				type;
	struct s_word	*next;
	struct s_word	*prev;
}				t_word;

typedef struct s_file
{
	char			*name;
	int				fd;
	int				type;
	struct s_file	*next;
	struct s_file	*prev;
}				t_file;

typedef struct s_cmd
{
	char				*path;
	char				**args;
	int					type;
	int					pid;
	int					in;
	int					out;
	struct s_file		*to_read;
	struct s_file		*to_write;
	struct s_cmd		*next;
	struct s_cmd		*prev;
	struct s_operation	*sub;
}				t_cmd;

typedef struct s_operation
{
	int					type;
	int					s_exec;
	struct s_operation	*next;
	struct s_operation	*prev;
	struct s_cmd		*cmd;
}				t_operation;

extern int		g_signal_status;

// FRONT >>>
void			config_cmd_sig(int is_reset);
void			heredoc_sig(int status);
void			readline_sig(int status);
char			*get_prompt(char *station);
char			*get_station(char *session);

// TOKENIZER >>>
int				tokenize_input(char *input, t_word **lst, t_env *env);
int				is_space(char c);
int				is_sgl_token(char *input);
int				is_dbl_token(char *input);
int				isnt_token_end(char *input);
int				generate_token(char *str, int len, t_word **lst, t_env *env);
int				attribute_type(char *token);
int				transform_t(t_word *token);
int				handle_quotes(char *input, char c);
int				unclosed_q(char *token);
char			*handle_expand(char *str, t_env *env);
char			*get_token_content(char *str, t_env *env);
int				is_end_join(char c, char sep);

// ANALYZER >>>
int				should_parse(char *input);
int				analyze_syntax(t_word **lst);
int				analyze_token(t_word *token);
int				analyze_operator(t_word *token);
int				analyze_redirect(t_word *token);
int				analyze_par(t_word *token);
int				analyze_closure(t_word *token);

// PARSER >>>
int				parse_tree(t_word **tokens, t_operation **ops, t_env *env);
int				generate_tree(t_word *t, t_operation **ops, t_env *env);
int				set_file_cmd(t_word *t, t_cmd *cmd);
int				set_arg_cmd(t_word *t, t_cmd *cmd);
int				set_path_cmd(t_word *t, t_cmd *cmd, t_env *env);
t_word			*skip_parenthesis(t_word *token);
int				check_cmd_path(char **str, char *path, char *exec);
int				here_doc(char *eof, t_env *env);
int				set_file(t_file *current, t_env *env);

// EXEC >>>
int				execute_tree(t_operation **ops, t_env *env);
void			init_files(t_cmd **cmds, t_env *env);
void			init_pipes(t_cmd **cmds);
void			close_pipes(t_cmd **cmds);
int				should_exec(t_operation *op);
int				check_cmd(t_cmd *current);
int				wait_for_all(t_cmd **cmds);
void			error_from_exec(t_cmd **cmds, int why);
void			return_error(void);
int				handle_wildcard(char ***args);

// STRUCT >>>
t_word			*ft_wordnew(char *str);
void			ft_wordadd_back(t_word *new, t_word **lst);
t_cmd			*ft_cmdnew(int type);
void			ft_cmdadd_back(t_cmd *new, t_cmd **lst);
t_cmd			*ft_cmdlast(t_cmd *cmd);
t_operation		*ft_opnew(int type);
void			ft_opadd_back(t_operation *new, t_operation **lst);
t_operation		*ft_oplast(t_operation *op);
t_file			*ft_filenew(char *str, int type);
void			ft_fileadd_back(t_file *new, t_file **lst);
void			free_file(t_file **lst);
int				init_env(t_env *local_env, char **env);
void			free_env(t_env *local_env);
void			entry_lstadd_front(t_entry_list **lst, t_entry_list *new);
void			lst_to_tab(char ***args, t_entry_list *lst);
size_t			entry_lstlen(t_entry_list *lst);
t_entry_list	*entry_lstnew(char *entry_name);
t_entry_list	*entry_lstlast(t_entry_list *lst);

// FREE >>>
void			free_parse(t_word **token, t_operation **operations);
void			free_words(t_word **lst);
void			free_operations(t_operation **lst);
void			free_cmds(t_cmd **lst);
void			free_tab_str(char **tab, char *str);

// DEV >>>
void			print_tab(char **tab);
void			print_lst_word(t_word *lst);
void			print_tree(t_operation **ops, int is_sub);
void			print_cmds(t_cmd **cmds);

// BUILT_INS >>>
int				ft_pwd(void);
int				ft_cd(char **args);
int				ft_env(char **env, int from_export);
int				ft_echo(char **args);
int				ft_export(char **args, t_env *env);
int				ft_unset(char **args, t_env *env);
int				exec_export(char *arg, t_env *env);
int				find_var_pos(char *var_name, char **env, size_t *pos);
int				check_identifier(char *str);
void			sort_env(char ***env);

#endif
