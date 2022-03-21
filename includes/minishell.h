/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:42:30 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/21 15:34:07 by hel-makh         ###   ########.fr       */
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
	L_PAREN,
	R_PAREN,
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

typedef struct s_cmd {
	char			**cmd;
	int				type;
	int				subsh_lvl;
	t_list			*redirect;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_vars {
	char			**envp;
	char			*cmdline;
	char			*last_cmdline;
	t_list			*tokens;
	t_cmd			*cmds;
}	t_vars;

int		ft_strcmp(const char *s1, const char *s2);
void	*ft_free(void *ptr);
void	*ft_free_2d(char **ptr);
void	*ft_free_3d(char ***ptr);
size_t	ft_arrlen(char **arr);
char	**ft_add_str2arr(char **array, char *str);

t_list	*ft_lstnew(char *content, int type);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
int		ft_lstsize(t_list *lst);

t_cmd	*ft_cmd_lstnew(char **cmd, int type, int subsh_lvl, t_list *redirect);
t_cmd	*ft_cmd_lstlast(t_cmd *lst);
void	ft_cmd_lstadd_back(t_cmd **lst, t_cmd *new);
void	ft_cmd_lstclear(t_cmd **lst);
int		ft_cmd_lstsize(t_cmd *lst);

void	ft_init_vars(int argc, char *argv[], char *envp[], t_vars *vars);
void	ft_handle_signals(int sig);
void	ft_tokenization(t_vars *vars);
int		ft_verify_syntax(t_vars *vars);
int		ft_parse_cmds(t_vars *vars);
void	ft_free_program(t_vars *vars);

#endif