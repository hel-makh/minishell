/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:42:30 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/26 12:37:30 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "../Libft/libft.h"

# define PROMPT "minishell$ "

int exit_status;

enum e_type {
	WORD,
	D_QUOTE,
	S_QUOTE,
	L_PAREN,
	R_PAREN,
	D_RED_IN,
	D_RED_OUT,
	RED_IN,
	RED_OUT,
	AND,
	OR,
	PIPE
};
/*
typedef struct s_exec
{
	int		count;
	int 	total_pipes;
	int		fd_in;
	int		fd_out;
	int		pipes;
	int		*fd;
	int		i;
	int		j;
	pid_t		pid;
	char	*line;
	char	*str;
	int		fd_tmp;
	int		status;
}   t_exec;
*/
typedef struct s_env {
	char			**envp;
	struct s_env	*next;
}	t_env;

typedef struct s_list {
	char			*content;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd {
	char			**cmd;
	int				type;
	int				*subsh_lvl;
	t_list			*redirect;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe {
	int				fd[2];
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_vars {
	char			*cmdline;
	char			*last_cmdline;
	t_env			*envp;
	t_list			*tokens;
	t_cmd			*cmds;
	t_pipe			*pipes;
	// t_exec			*exec;
}	t_vars;

int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(char *content, int type);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);

int		ft_cmd_lstsize(t_cmd *lst);
t_cmd	*ft_cmd_lstnew(char **cmd, int type, int *subsh_lvl, t_list *redirect);
t_cmd	*ft_cmd_lstlast(t_cmd *lst);
void	ft_cmd_lstadd_back(t_cmd **lst, t_cmd *new);
void	ft_cmd_lstclear(t_cmd **lst);

int		ft_env_lstsize(t_env *lst);
t_env	*ft_env_lstnew(char **envp);
t_env	*ft_env_lstlast(t_env *lst);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
void	ft_env_lstclear(t_env **lst);

int		ft_pipe_lstsize(t_pipe *lst);
t_pipe	*ft_pipe_lstnew(int input, int output);
t_pipe	*ft_pipe_lstlast(t_pipe *lst);
void	ft_pipe_lstadd_back(t_pipe **lst, t_pipe *new);
void	ft_pipe_lstclear(t_pipe **lst);

char	*ft_remove_quotes(char *s);
int		ft_wc_strcmp(const char *s1, const char *s2);
char	*ft_getenv(char *var, t_env *envp);

int		ft_init_vars(t_vars *vars, char *envp[]);
void	ft_handle_signals(int sig);
int		ft_tokenization(t_vars *vars);
int		ft_verify_syntax(t_vars *vars);
int		ft_parse_cmds(t_vars *vars);
void	ft_expand_env_vars(t_vars *vars);
void	ft_expand_wildcards(t_vars *vars);
void	ft_free_program(t_vars *vars);

// execution
int		exec_cmd_skip(t_cmd *cmd);
void	execute_cmds(t_vars *vars);
void	exec_cmd(t_cmd **cmd, t_vars *vars);
void	exec_cmd_child(t_cmd *cmd, t_vars *vars);
void	the_execution(t_cmd *cmd, t_vars *vars);
// void	heredoc_exec(t_exec *exec, char *end);
void	exit_perror(void);
void	exit_cmd_notfound(char *cmd, int exit_status);

// pipes
int		get_pipes_count(t_cmd *cmd);
void	init_pipes(t_pipe **p, int count);
void	close_pipes(t_pipe **p, int count);
int		redirect_input(t_list *redirect);
int		redirect_output(t_list *redirect);

// built-ins
int		is_built_in(char *name);
int		exec_built_in(char **cmd);
int		echo_builtin(char **cmd);
int		cd_build(char **cmd);
int		pwd_cmd();

#endif