/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:44:10 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/25 12:08:24 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_syntax {
	int		d_quotes;
	int		s_quotes;
	int		parentheses;
}	t_syntax;

static int	ft_verify_qandp(t_vars *vars)
{
	t_syntax	syntax;
	t_list		*t_tokens;

	syntax.d_quotes = 0;
	syntax.s_quotes = 0;
	syntax.parentheses = 0;
	t_tokens = vars->tokens;
	while (t_tokens)
	{
		if (t_tokens->type == D_QUOTE)
			syntax.d_quotes ++;
		if (t_tokens->type == S_QUOTE)
			syntax.s_quotes ++;
		if (t_tokens->type == L_PAREN)
			syntax.parentheses ++;
		if (t_tokens->type == R_PAREN)
			syntax.parentheses --;
		t_tokens = t_tokens->next;
	}
	if (syntax.d_quotes % 2 != 0 || syntax.s_quotes % 2 != 0
		|| syntax.parentheses != 0)
		return (0);
	return (1);
}

static int	ft_verify_pipe_oanda(t_vars *vars)
{
	t_list		*t_tokens;
	int			is_word;

	is_word = 0;
	t_tokens = vars->tokens;
	while (t_tokens)
	{
		if (t_tokens->type == WORD)
			is_word = 1;
		if (is_word
			&& (t_tokens->type == AND
				|| t_tokens->type == OR
				|| t_tokens->type == PIPE))
			is_word = 0;
		else if (!is_word
			&& (t_tokens->type == AND
				|| t_tokens->type == OR
				|| t_tokens->type == PIPE))
			return (0);
		t_tokens = t_tokens->next;
	}
	if (!is_word)
		return (0);
	return (1);
}

static int	ft_verify_redirections(t_vars *vars)
{
	t_list		*t_tokens;

	t_tokens = vars->tokens;
	while (t_tokens)
	{
		if ((t_tokens->type == RED_IN
				|| t_tokens->type == RED_OUT
				|| t_tokens->type == D_RED_IN
				|| t_tokens->type == D_RED_OUT)
			&& (!t_tokens->next
				|| (t_tokens->next
					&& t_tokens->next->type != WORD)))
			return (0);
		t_tokens = t_tokens->next;
	}
	return (1);
}

static int	ft_verify_parenthesis(t_vars *vars)
{
	t_list		*t_tokens;

	t_tokens = vars->tokens;
	while (t_tokens)
	{
		if ((t_tokens->next && t_tokens->next->type == L_PAREN
				&& t_tokens->type != AND
				&& t_tokens->type != OR
				&& t_tokens->type != PIPE
				&& t_tokens->type != L_PAREN)
			|| (t_tokens->type == R_PAREN
				&& t_tokens->next
				&& t_tokens->next->type == WORD))
			return (0);
		t_tokens = t_tokens->next;
	}
	return (1);
}

int	ft_verify_syntax(t_vars *vars)
{
	if (!ft_verify_qandp(vars)
		|| !ft_verify_pipe_oanda(vars)
		|| !ft_verify_redirections(vars)
		|| !ft_verify_parenthesis(vars))
		return (0);
	return (1);
}
