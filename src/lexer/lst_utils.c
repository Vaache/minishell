/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:52:49 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/14 21:50:59 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*lstadd(char *string, t_type type, int prc, int flag);
t_tok	*lstlast(t_tok *lst);
void	lstback(t_tok **pars, t_tok *new);
void	lstclear(t_tok **lst);
int		lstsize(t_tok *lst);

t_tok	*lstadd(char *string, t_type type, int prc, int flag)
{
	t_tok		*tmp;

	tmp = (t_tok *)malloc(sizeof(t_tok));
	if (!tmp)
		return (NULL);
	tmp->cmd = ft_strdup(string);
	tmp->hdoc_fname = NULL;
	tmp->flag = flag;
	tmp->prc = prc;
	tmp->type = type;
	tmp->err_code = 0;
	tmp->last_red = -1;
	tmp->last_hdoc = 0;
	tmp->last_input = -1;
	tmp->sub = 0;
	tmp->fd = -42;
	tmp->_stdin_ = -42;
	tmp->_stdout_ = -42;
	tmp->stdin_backup = -42;
	tmp->stdout_backup = -42;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

void	lstback(t_tok **pars, t_tok *new)
{
	t_tok	*tmp;

	tmp = lstlast(*pars);
	if (!tmp)
		*pars = new;
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

void	lstclear(t_tok **lst)
{
	t_tok	*ptr;

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

t_tok	*lstlast(t_tok *lst)
{
	t_tok	*tmp;

	tmp = lst;
	if (!tmp)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	lstsize(t_tok *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		(lst) = (lst)->next;
	}
	return (i);
}
