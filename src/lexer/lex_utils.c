/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:11:09 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/08 12:15:43 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char *str, int i, int j);
int	is_delim(t_pars	*pars);

int	ft_isspace(char *str, int i, int j)
{
	while (i < j && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	is_delim(t_pars	*pars)
{
	t_pars	*tmp;

	tmp = lstlast(pars);
	if (!tmp)
		return (0);
	else if (tmp->type == PIPE || tmp->type == HEREDOC)
		return (1);
	else if (tmp->type == SUBSH_CLOSE || tmp->type == SUBSH_OPEN)
		return (1);
	else if (tmp->type == WRITE_APPEND || tmp->type == WRITE_TRUNC)
		return (1);
	else if (tmp->type == XOR || tmp->type == XAND)
		return (1);
	else
		return (0);
}
