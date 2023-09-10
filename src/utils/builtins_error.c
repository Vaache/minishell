/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:30:58 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/08 20:45:26 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_error(char	*str, char *err);

void	builtins_error(char	*str, char *err)
{
	if (!ft_strcmp(str, "cd") && err == NULL)
		ft_printf(2, "cd: error retrieving current directory: %s%s\n", \
					"getcwd: cannot access parent directories: ", \
					"No such file or directory");
	else if (!ft_strcmp(str, "export") && err)
		ft_printf(2, "Minishell: export: `%s': not a %s\n", \
					err, "valid identifier");
	else if (!ft_strcmp(str, "unset") && err)
		ft_printf(2, "Minishell: unset: `%s': not a %s\n", \
					err, "valid identifier");
	g_exit_status_ = -42;
}
