/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:43:45 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/31 21:47:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_init(t_main *main)
{
	main->lex = NULL;
	main->pars = NULL;
	main->temp = NULL;
	main->path = NULL;
	main->flag = 1;
	main->hdoc = 0;
	main->redir = 0;
	main->input = 0;
	main->stdin_backup = -42;
	main->stdout_backup = -42;
	main->exit_status = 0;
}
