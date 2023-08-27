/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:24:02 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/25 22:31:39 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_count(char *limiter);

int	quote_count(char *limiter)
{
	int	dquote;
	int	squote;
	int	i;
	
	i = -1;
	dquote = ((squote = 0));
	while (limiter && limiter[++i])
	{
		if (limiter[i] == '"')
			dquote++;
		if (limiter[i] == '\'')
			squote++;
	}
	if (dquote % 2 != 0 || squote % 2 != 0 || squote == 1 || dquote == 1)
		return (1);
	return (0);
}