/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:04:04 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/15 18:27:02 by vhovhann         ###   ########.fr       */
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
	main->pars = NULL;
	main->lex = NULL;
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
