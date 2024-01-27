/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:08:54 by bkas              #+#    #+#             */
/*   Updated: 2024/01/27 13:05:13 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define CMD_ERROR		"command not found"
# define CMD_NOT_FOUND	"No such file or directory || Permission denied"
# define SYNTAX_ERROR3	"syntax error near unexpected token `newline'"
# define SYNTAX_ERROR2	"syntax error near unexpected token `|'"
# define STD_IN		20
# define STD_OUT	30

# include <stdlib.h>
# include <sys/types.h>

int	g_signal;

typedef struct s_redir
{
	char			*type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_redirs
{
	t_redir	*input;
	t_redir	*output;
	t_redir	*cmd;
	char	**argv;
}	t_redirs;

typedef struct s_pipe
{
	int				fd[2];
	pid_t			pid;
	int				status;
	char			*cmd;
	char			**argv;
	char			*file;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_ms
{
	char		**cmd;
	char		**path;
	char		**envp;
	char		*line;
	char		*tmp;
	char		*prompt;
	char		*path_cmd;
	char		*path_tmp;
	int			status;
	int			status2;
	int			flag;
	int			built_in;
	t_env		*env;
	t_env		*export;
	t_pipe		*pipe;
	t_redirs	*redir;
}	t_ms;

typedef struct s_vars
{
	int		count;
	char	nail;
	char	*ret;
	char	*tmp;
	char	*tmp2;
	char	*join;
	char	**cmd;
	char	*name;
	char	*full_name;
	int		quate;
	size_t	quate2;
	size_t	i;
	size_t	j;
	size_t	q;
	size_t	q2;
	int		redir;
	int		k;
	int		c;
}	t_vars;

//**********************************************//
//		UTILS FUNCTIONS				//

void	ms_loop(t_ms *ms);
char	*find_path(t_ms *ms, char *cmd);
void	ms_init(t_ms *ms, char **envp);
void	remove_env(t_env **env, char *key);
t_env	*env_init(char **envp);
t_env	*env_manual_init(void);

//**********************************************//
//		PARSE FUNCTIONS				//

void	free_pipe(t_pipe *pipe);
t_pipe	*add_pipe(t_pipe *pipe, char *cmd);
int		add_pipes(t_ms *ms);
int		is_separator(char c);
int		count_tokens(const char *str);
int		count_tokens_continue(const char *str, int *i, int *k, char quate);
int		handle_dollar(t_ms *ms, t_vars *vars, char *cmd);
void	handle_quote(char *cmd, t_vars *vars, int flag, size_t i);
void	init_vars(t_vars *vars, int flag);
void	quate_zero(t_vars *vars, char *cmd, size_t k);

void	dollar_continue(char *cmd, size_t *i, size_t *j);
void	getenv_name(t_ms *ms, char *cmd, t_vars *vars, char **ret);

char	**add_cmd(char *str, t_ms *ms);
int		in_nail(t_vars *vars, char *str);
int		adding_vars(t_ms *ms, t_vars *vars, char **str);
int		is_null(t_vars *vars);
int		is_not_nail(t_vars *vars, char *str);
int		is_null_again(t_vars *vars);
int		is_full_sep(t_vars *vars, char *str);
void	add_null(t_vars *vars);

//**********************************************//
//		EXECUTE FUNCTIONS			//

void	execute_full(t_ms *ms);
void	execute_full_pipe(t_ms *ms);

void	execute(char *file, char **argv, char **envp, t_ms *ms);
void	sequential_pipe(t_pipe *process, char **envp, t_ms *ms);
void	next_process(t_pipe *process, char **envp, t_ms *ms);
int		not_redir(t_ms *ms, char **cmd, pid_t pid);
void	sequential_pipe_exit(t_pipe *process, t_ms *ms);
void	wait_child(t_pipe *process, t_ms *ms);
int		is_heredoc(char *argv);
void	wait_process(t_pipe *process);
void	child_pipe(t_pipe *process, char **envp, t_ms *ms);
void	next_child(t_pipe *process, char **envp, t_ms *ms);
void	next_parent(t_pipe *process, char **envp, t_ms *ms);
void	fork_exit(char *str);

//**********************************************//
//					EXIT CODE					//

void	update_exit_code(t_ms *ms);
void	clean_ms(t_ms *ms, int flag);
void	free_env(t_env *env);

//**********************************************//
//		BUILT-IN FUNCTIONS				//

int		built_in(char **argv, t_ms *ms);
char	*find_env(t_env *envp, char *name);
int		has_env(t_env *envp, char *name);
int		add_env(t_env **envp, char *name, char *value);
char	*dollar_parse(t_ms *ms, char *cmd);
int		unset(char **argv, t_ms *ms);
int		export(char **argv, t_ms *ms);
int		print_export(t_env **envp);
int		sort_export(t_env **envp, char *temp_name, char *temp_value);
int		echo(char **argv);
int		cd(t_ms *ms, char **argv);
int		pwd(void);
int		env(t_env *envp);
int		exit_shell(char **argv, t_ms *ms);
char	**exit_controls(t_ms *ms, char **argv);
void	syntax_ctrl(char **argv, t_ms *ms);
void	safe_exit(t_ms *ms, int status, char **argv, int flag);

//**********************************************//
//		REDIR FUNCTIONS				//

int		redir_check(t_redir *redir, t_ms *ms);
char	**redir_exe(t_ms *ms, char *argv);
void	redir_order(t_redirs *redir, t_ms *ms);
void	redir_heredoc(t_redir *redir, t_ms *ms);
char	*re_create_cmd(t_redir *lst);
void	redir_add(t_redirs	*redir, char **command, int *i);
void	redir_none(t_redirs	*redir, char **command, int *i);
void	redir_init_r(t_redirs	*redir, char **command, int *i);
void	redir_init_l(t_redirs	*redir, char **command, int *i);
void	free_redirs(t_redirs *redir);

int		is_redir(char *str);
int		redir_execute(t_ms *ms, char *argv);
void	print_error(char *cmd, char *error);
int		redir_syntax_check(char *str);

#endif
