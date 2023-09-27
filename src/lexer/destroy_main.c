/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:04:04 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/27 17:16:42 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_structure(t_tok *root);
void	destroy_main(t_main *main);

void	destroy_main(t_main *main)
{
	if (!main)
		return ;
	destroy_structure(main->lex);
	destroy_structure(main->pars);
	main->hdoc = 0;
	main->redir = 0;
	main->input = 0;
	if (main->path)
		free_2d(main->path);
	main->path = NULL;
	main->lex = NULL;
	main->pars = NULL;
	main->temp = NULL;
	main->last_hdoc = -42;
}

void	destroy_structure(t_tok *root)
{
	if (!root)
		return ;
	if (root->right)
		destroy_structure(root->right);
	if (root->left)
		destroy_structure(root->left);
	if (root->next)
		destroy_structure(root->next);
	if (root->hdoc_fname && root->type == HEREDOC)
	{
		unlink (root->hdoc_fname);
		free(root->hdoc_fname);
	}
	if (root->cmd)
		free (root->cmd);
	free (root);
	root = NULL;
	return ;
}
