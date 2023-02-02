/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicoque.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:31:55 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/02 11:48:33 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINICOQUE_H
# define MINICOQUE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <ft_boolean.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"

# define BLANK 0
# define COMMAND 0
# define LITERAL 1
# define PATH 1
# define PIPE 2 
# define ARGS 3
# define S_QUOTE 3 
# define D_QUOTE 4 
# define REDIRECT 5
# define HEREDOC 6
# define DOLLAR 7
# define NUULL 8
# define PCOLOR "\001\e[0;36m\002"
# define RESET   "\001\e[0m\002"

typedef struct s_token {
	char			*str;
	int				token_type;
}	t_token;

typedef struct s_btree {
	char			**tab_str;
	int				type;
	struct s_btree	*left;
	struct s_btree	*right;
}				t_btree;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	int					declared;
	int					index;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_minicoque
{
	t_env_var	*env_var;
	pid_t		*curprocess;
}	t_minicoque;

/*	env_clst_utils.c	*/

int			get_env_size(t_env_var *env);
char *const	*env_to_array(t_env_var *env);

/*	echo.c	*/

int			echo(char **args);

/*	env.c	*/

int			env(t_env_var *env_data, char **args);

/*	export.c	*/

int			export(t_env_var *env, char **args);

/*	unset.c	*/

int			unset(t_env_var *env, char **args);

/*	pwd.c	*/

int			pwd(void);

/*	cd.c	*/

int			cd(t_env_var *env, char **args);

/*	exit.c	*/

void		ft_exit(char **args, t_minicoque *data);

/*	t_env_utils.c */

t_env_var	*create_env(char *path);
void		ft_env_add_back(t_env_var **lst, t_env_var *new);
void		replace_value(t_env_var *env, char *path);
t_env_var	*get_env(t_env_var *lst, char *path);

/*	env_last_exit	*/

int			last_exit(t_bool get, int error);

/*	free_utils.c	*/

void		d_tab_free(char **elem);
void		s_free(void *elem);
void		free_coque_data(t_minicoque *data);

/*	tree_exec_utils.c	*/

void		init_tree_exec(t_minicoque *data, t_btree *root);
int			countcmd(t_btree *tree);

/*	fd_utils.c	*/

void		set_exit_fd(t_btree *curbranch, int type, int fds[2], int fd);
int			get_entry_fd(int fds[2], t_btree *curbranch);
int			ft_close_fd(int fd, t_bool force);
void		secure_dup2(int source, int target);

/*	get_cmd_utils.c	*/

char		**token_to_array(t_token **token);
char		*get_cmds(char *av, char *const *envp);

/*	tab_utils.c	*/

char		**tab_dup(char	**tab_str);
size_t		strtab_len(char **str_tab);

/*	lexer.c	*/

t_token		**lexer(char *av, t_env_var *env);

/*	token_utils.c	*/

void		free_token(t_token **token_tab);
t_token		**init_tokentab(char *input);
void		pipe_token(t_token **token_tab, int *nb, char *input, int *i);
void		redirect_token(t_token *token, char *input, int *i);
int			token_tab_len(t_token **tab, int redir);

/*	ft_execute.c	*/

void		ft_execute(t_minicoque *data, t_btree *root, int fds[2], int pipe);

/*	exec_utils.c	*/

int			*ft_setcur(t_btree *root);
t_bool		ft_isforkable(char *function, char *arg);

/*	individual_exec_utils.c	*/

void		ft_exec(t_btree *branch, t_minicoque *data);
void		last_exec(t_minicoque *data, t_btree *root, int fds[2]);
void		child_cmd(int fds[2], t_minicoque *data, t_btree *root);
void		ft_single_exec(t_minicoque *data, t_btree *root, int fds[2]);

/*	param_expansion_functions.c	*/

char		*doll_management(char *input, t_env_var *env);

/*	parsing_utils.c	*/

int			typify(int c);
int			digit_str(char *str);
t_token		*sub_token_create(t_token **token_tab, int pos);
t_token		**sub_token_tab(t_token **token_tab, int start, int len);

/*	counting_functions.c	*/

int			token_count(char *input);

/*	counting_utils.c	*/

int			pipe_count(char *input, int *i, int *nb);
int			pipe_token_count(t_token **token_tab);
void		counting_syntax_error(char input);
int			redirect_count(char *input, int *i, int *nb);

/*	parsing.c	*/

t_btree		*parsing(t_token **token_tab, t_env_var *var);

/*	tree_creation_utils.c	*/

t_btree		*init_tree_node(void);
t_btree		*insert_node(t_token **token_array);
t_btree		*insert_cmd_node(char *cmd, t_env_var *env);
int			is_builtin(char	*str);

/*	quotes_magement_functions.c	*/

char		*quotes_management(char *input, t_env_var *env, int *i);

/*	redirection_parsing.c	*/

char		**redirtab_create(t_token **token_tab);

/*	redirect_parsing_utils.c	*/

int			redirect_syntax_check(char *input, int *i);
int			redir_in_count(t_token **token_count);
int			redir_out_count(t_token **token_count);
char		*get_redir(char *str);
char		*get_redir_type(t_token **token_tab);

/*	heredoc_functions.	*/

int			heredoc(t_token **token_tab);
int			heredoc_count(t_token **token_tab);
char		*redir_heredoc(t_token **token_tab);

/*	heredoc_fork.c	*/

void		read_heredoc(t_token **token_tab, char *path);

/*	heredoc_utils.c	*/

int			heredoc_count(t_token **token_tab);
char		*redir_heredoc(t_token **token_tab);
int			hdoc_pipe_count(t_token **token_tab);
char		*init_heredoc_path(int pipe_nb);

/*	error_uils.c	*/

int			isfile(const char* name);

#endif
