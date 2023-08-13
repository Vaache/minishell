/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:52:49 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/12 21:35:11 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*lstadd(char *string, t_type type, int prc, int flag);
t_pars	*lstlast(t_pars *lst);
void	lstback(t_pars **pars, t_pars *new);
void	lstclear(t_pars **lst);

t_pars	*lstadd(char *string, t_type type, int prc, int flag)
{
	t_pars	*tmp;

	tmp = (t_pars *)malloc(sizeof(t_pars));
	if (!tmp)
		return (NULL);
	tmp->cmd = ft_strdup(string);
	tmp->err_code = 0;
	tmp->flag = flag;
	tmp->prc = prc;
	tmp->type = type;
	tmp->subshell_code = 0;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

void	lstback(t_pars **pars, t_pars *new)
{
	t_pars	*tmp;

	tmp = lstlast(*pars);
	if (!tmp)
		*pars = new;
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

void	lstclear(t_pars **lst)
{
	t_pars	*ptr;

	ptr = NULL;
	if (!lst || !*lst)
		return ;
	while ((*lst))
	{
		ptr = (*lst)->next;
		free ((*lst)->cmd);
		free (*lst);
		(*lst) = ptr;
	}
	ptr = NULL;
}

t_pars	*lstlast(t_pars *lst)
{
	t_pars	*tmp;

	tmp = lst;
	if (!tmp)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
