/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:56:02 by labdello          #+#    #+#             */
/*   Updated: 2024/09/06 17:04:12 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_word
{
	char			*content;
	int				type;
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;

typedef struct s_files
{
	int		in;
	int		out;
}	t_files;

typedef struct s_cmd
{
	char				*path;
	char				**args;
	int					type;
	int					pid;
	int					to_read;
	int					to_write;
	struct s_cmd		*next;
	struct s_cmd		*prev;
	struct s_operation	*sub;
}	t_cmd;

typedef struct s_operation
{
	int					type;
	struct s_operation	*next;
	struct s_operation	*prev;
	struct s_cmd		*cmd;
}	t_operation;

// FRONT >>>
void		signal_handler(int status);
char		*get_prompt(char *station);
char		*get_station(char *session);

// TOKENIZER >>>
int			tokenize_input(char *input, t_word **lst);
int			is_space(char c);
int			is_sgl_token(char *input);
int			is_dbl_token(char *input);
int			isnt_token_end(char *input);
int			generate_token(char *str, int len, t_word **lst);
int			attribute_type(char *token);
int			transform_t(t_word *token);
int			handle_quotes(char *input, char c);
int			unclosed_q(char *token);
char		*handle_expand(char *str);
char		*get_token_content(char *str);
int			is_end_join(char c, char sep);

// ANALYZER >>>
int			analyze_syntax(t_word **lst);
int			analyze_token(t_word *token);
int			analyze_operator(t_word *token);
int			analyze_redirect(t_word *token);
int			analyze_par(t_word *token);
int			analyze_closure(t_word *token);

// PARSER >>>
int			parse_tree(t_word **tokens, t_operation **ops);
int			generate_tree(t_word *t, t_operation **ops);
int			set_file_cmd(t_word *t, t_cmd *cmd);
int			set_arg_cmd(t_word *t, t_cmd *cmd);
int			set_path_cmd(t_word *t, t_cmd *cmd);
t_word		*skip_parenthesis(t_word *token);
int			check_cmd_path(char **str, char *path, char *exec);
int			here_doc(char *eof);

// EXEC >>>

// STRUCT >>>
t_word		*ft_wordnew(char *str);
void		ft_wordadd_back(t_word *new, t_word **lst);
t_cmd		*ft_cmdnew(int type);
void		ft_cmdadd_back(t_cmd *new, t_cmd **lst);
t_cmd		*ft_cmdlast(t_cmd *cmd);
t_operation	*ft_opnew(int type);
void		ft_opadd_back(t_operation *new, t_operation **lst);
t_operation	*ft_oplast(t_operation *op);

// FREE >>>
void		free_parse(t_word **token, t_operation **operations);
void		free_words(t_word **lst);
void		free_operations(t_operation **lst);
void		free_cmds(t_cmd **lst);
void		free_tab_str(char **tab, char *str);

// DEV >>>
void		print_tab(char **tab);
void		print_lst_word(t_word *lst);
void		print_tree(t_operation **ops, int is_sub);
void		print_cmds(t_cmd **cmds);

// BUILT_INS >>>
int			ft_env(char **env);
int			ft_export(char **args, char ***env);
int			ft_unset(char **args, char ***env);
int			find_var_pos(char *var_name, char **env, size_t *pos);

#endif
