/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:10:27 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/08 20:41:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space(t_pars **pars, char *line, int i, int start);

void	handle_space(t_pars **pars, char *line, int i, int start)
{
	if (ft_isspace(line, start, i))
		return ;
	else if (is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 3));
	else
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 2));
}
