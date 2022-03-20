/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:42:30 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 15:55:55 by hel-makh         ###   ########.fr       */
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

typedef struct s_list {
	char			*content;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_commands {
	char			**command;
	t_list			*redirection;
}	t_commands;

typedef struct s_vars {
	char			**envp;
	char			*cmdline;
	char			*last_cmdline;
	t_list			*tokens;
	t_commands		*commands;
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
t_list	*ft_lstnew(char *data, int type);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
int		ft_lstsize(t_list *lst);

void	ft_init_vars(int argc, char *argv[], char *envp[], t_vars *vars);
void	ft_handle_signals(int sig);
void	ft_tokenization(t_vars *vars);
int		ft_verify_syntax(t_vars *vars);
// void	ft_exec_pipeline(t_vars *vars, int index);
void	ft_free_program(t_vars *vars);

#endif