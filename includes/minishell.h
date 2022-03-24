/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:42:30 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/24 15:45:59 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
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

int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(char *content, int type);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);

int		ft_cmd_lstsize(t_cmd *lst);
t_cmd	*ft_cmd_lstnew(char **cmd, int type, int subsh_lvl, t_list *redirect);
t_cmd	*ft_cmd_lstlast(t_cmd *lst);
void	ft_cmd_lstadd_back(t_cmd **lst, t_cmd *new);
void	ft_cmd_lstclear(t_cmd **lst);

char	*ft_remove_quotes(char *s);
int		ft_wc_strcmp(const char *s1, const char *s2);
char	*ft_getenv(char *var, char *envp[]);

int		ft_init_vars(t_vars *vars, char *envp[]);
void	ft_handle_signals(int sig);
int		ft_tokenization(t_vars *vars);
int		ft_verify_syntax(t_vars *vars);
int		ft_parse_cmds(t_vars *vars);
void	ft_expand_env_vars(t_vars *vars);
void	ft_expand_wildcards(t_vars *vars);
void	ft_free_program(t_vars *vars);

#endif