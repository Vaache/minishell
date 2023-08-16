/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:10:27 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/15 22:39:23 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space(t_pars **pars, char *line, int i, int start);

void	handle_space(t_pars **pars, char *line, int i, int start)
{
	char	*str;
	
	str = NULL;
	if (ft_isspace(line, start, i))
		return ;
	str = ft_substr(line, start, i - start);
	if (!ft_isspace(line, start, i) && is_delim(*pars))
		lstback(pars, lstadd(str, WORD, 0, 1));
	else if (start > 1 && line[start - 1] == ' ')
		lstback(pars, lstadd(str, WORD, 0, 2));
	else if (!ft_isspace(line, start, i))
		lstback(pars, lstadd(str, WORD, 0, 0));
	free(str);
}
