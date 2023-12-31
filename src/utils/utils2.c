/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:53:27 by vhovhann          #+#    #+#             */
/*   Updated: 2023/10/01 14:14:19 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_mode(char *s1, char *s2, int mode);
char	*trim_zeroes(char *s);
int		error_code(int error_num);

char	*trim_zeroes(char *s)
{
	int		j;
	char	*str;

	j = 0;
	str = NULL;
	if (s[j] == '-' || s[j] == '+')
		j++;
	if (s[j] == '0' || (s[j] == '0' && s[j + 1] == '0'))
	{
		while (s && s[j] != '\0')
		{
			while (s[j] != '\0' && s[j] == '0')
				j++;
			if (s[j] != '0')
				break ;
		}
		if (s[j] == '\0')
		{
			str = ft_strdup("0");
			return (str);
		}
		return (&s[j]);
	}
	return (s);
}

char	*strjoin_mode(char *s1, char *s2, int mode)
{
	if (mode == 1)
		s1 = ft_strjoin(s1, "\n", 1);
	else
		s1 = ft_strjoin(s1, " ", 1);
	s1 = ft_strjoin(s1, s2, 1);
	return (s1);
}

int	error_code(int error_num)
{
	if (error_num == 256)
		return (1);
	return (error_num % 256);
}

int	check_subsh(t_tok *stack)
{
	t_tok	*temp;

	temp = stack;
	while (temp)
	{
		if (temp->sub)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	fill_command(t_tok *tok)
{
	t_tok	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (check_types(tmp->type) == 2 && tmp->type != HEREDOC && \
			(tmp->next->next->type == WORD || tmp->next->next->type == DQUOTE || \
				tmp->next->next->type == SQUOTE))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
