/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:10:27 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/13 12:19:06 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space(t_pars **pars, char *line, int i, int start);

void	handle_space(t_pars **pars, char *line, int i, int start)
{
	char	*str;
	
	if (ft_isspace(line, start, i))
		return ;
	else if (is_delim(*pars))
	{
		str = ft_substr(line, start, i - start);
		lstback(pars, lstadd(str, WORD, 0, 3));
	}
	else
	{
		str = ft_substr(line, start, i - start);
		lstback(pars, lstadd(str, WORD, 0, 2));
	}
	free(str);
}
