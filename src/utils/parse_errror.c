/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:52:03 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/07 16:04:15 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_error(int fd, char *err);

int	parse_error(int fd, char *err)
{
	if (err[0] == '(')
		ft_printf(fd, "minishell: Syntax error missing token `%s'\n", ")");
	else
		ft_printf(fd, "%s", err);
	return (0);
}