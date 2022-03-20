/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:42:30 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/19 18:09:12 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include "../Libft/libft.h"

# define PROMPT "minishell$ "

enum e_type {
	WORD,
	D_QUOTE,
	S_QUOTE,
	R_PAREN,
	L_PAREN,
	D_RED_IN,
	D_RED_OUT,
	RED_IN,
	RED_OUT,
	AND,
	OR,
	PIPE,
	WILDCARD
};

typedef struct s_token {
	char			*data;
	int				type;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_vars {
	char	**envp;
	char	*cmdline;
	t_token	*tokens;
	char	quote;
	// char	**pipeline;
	// int		cmd_count;
	// char	*redirect_input;
	// char	*redirect_output;
	// char	*redirect_append;
	// char	*heredoc_delimiter;
	// int		p[2];
}	t_vars;

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnjoin(char const *s1, char const *s2, size_t n);
void	*ft_free(void *ptr);
void	*ft_free_2d(char **ptr);
void	*ft_free_3d(char ***ptr);
size_t	ft_arrlen(char **arr);

char	**ft_split_args(char const *s);
// char	**ft_split_pipes(char const *s);
char	*ft_getenv(char *var, char *envp[]);
char	*ft_cmdpath(t_vars *vars, char *cmd);
char	**ft_execve_args(t_vars *vars, char *cmd);
t_token	*ft_token_lstnew(char *data, int type);
t_token	*ft_token_lstlast(t_token *lst);
void	ft_token_lstadd_back(t_token **lst, t_token *new);
void	ft_token_lstclear(t_token **lst);
int		ft_token_lstsize(t_token *lst);

void	ft_init_vars(int argc, char *argv[], char *envp[], t_vars *vars);
void	ft_handle_signals(int sig);
void	ft_tokenization(t_vars *vars);
int		ft_verify_syntax(t_vars *vars);
// void	ft_exec_pipeline(t_vars *vars, int index);
void	ft_free_program(t_vars *vars);

#endif