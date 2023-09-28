/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:43:45 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/28 15:11:23 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_init(t_main *main)
{
	main->hd = NULL;
	main->lex = NULL;
	main->pars = NULL;
	main->temp = NULL;
	main->path = NULL;
	main->flag = 1;
	main->hdoc = 0;
	main->redir = 0;
	main->input = 0;
	main->fd_err = 0;
	main->last_hdoc = -42;
	main->exit_status = 0;
	main->builtins_err = 0;
}
