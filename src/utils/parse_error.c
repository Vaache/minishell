/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:52:03 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/10 16:22:39 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_error(int fd, char *err, int mode);

int	parse_error(int fd, char *err, int mode)
{
	if (err[0] == '(')
		ft_printf(fd, "Minishell: Syntax error missing token `%s'\n", ")");
	else
		ft_printf(fd, "Minishell : Syntax Error Near Unexpected Token `%s'\n", \
			err);
	if (mode == 1)
		free(err);
	return (0);
}
