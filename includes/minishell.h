/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:42:30 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/29 12:48:50 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "../Libft/libft.h"

# define PROMPT "minishell$ "

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

/***********************[ Structers ]***********************/
typedef struct s_glob
{
	pid_t			pid;
	int				exit_status;
	int				heredoc;
	int				flag;
}	t_glob;

t_glob	g_glob;

typedef struct s_list {
	char			*content;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd {
	char			**cmd;
	int				type;
	int				pipe[2];
	int				*subsh_lvl;
	t_list			*redirect;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_vars {
	char			*cmdline;
	char			*last_cmdline;
	char			**envp;
	t_list			*tokens;
	t_cmd			*cmds;
}	t_vars;

/***********************[ Linked Lists ]***********************/
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

char	*ft_remove_quotes(char *s);
int		ft_wc_strcmp(const char *s1, const char *s2);
char	*ft_getenv(char *var, char **envp);

/**************************[ Utils ]**************************/
int		ft_init_vars(t_vars *vars, char *envp[]);
void	signals_handler(int sign);
void	ft_free_program(t_vars *vars);
void	signal_heredoc(int sign);
char	*get_next_line(int fd);


/*************************[ Parsing ]*************************/
int		ft_tokenization(t_vars *vars);
int		ft_verify_syntax(t_vars *vars);
int		ft_parse_cmds(t_vars *vars);
void	ft_expand_env_vars(char **envp, char **cmd);
int		ft_expand_wildcards(t_cmd **cmd, t_list **redirect, int *index);

/************************[ Execution ]************************/
int		exec_init_pipes(t_cmd **cmd);
void	execute_cmds(t_vars *vars);
pid_t	execute_cmd(t_cmd **cmd, t_vars *vars);
void	the_execution(t_cmd *cmd, t_vars *vars);
int		duplicate_redirections(t_cmd **cmd, t_vars *vars, int is_fork);
int		open_heredoc(char *limiter, char **envp);
void	exit_perror(void);
void	exit_cmd_notfound(char *cmd, int exit_status);

/************************[ Built-ins ]************************/
int		is_built_in(char *name);
int		exec_built_in(char **cmd, t_vars *vars);
int		builtin_echo(char **cmd);
int		builtin_pwd(void);
int		builtin_cd(char **cmd, char **envp);
int		builtin_env(char **envp);
int		builtin_export(char **cmd, char ***envp);
int		builtin_unset(char **cmd, char ***envp);
int		builtin_exit(char **cmd);

#endif