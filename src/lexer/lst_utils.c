/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:52:49 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/31 14:59:18 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*lstadd(char *string, t_type type, int prc, int flag);
t_pars	*lstlast(t_pars *lst);
void	lstback(t_pars **pars, t_pars *new);
void	lstclear(t_pars **lst);
int		lstsize(t_pars *lst);

t_pars	*lstadd(char *string, t_type type, int prc, int flag)
{
	t_pars		*tmp;

	tmp = (t_pars *)malloc(sizeof(t_pars));
	if (!tmp)
		return (NULL);
	tmp->cmd = ft_strdup(string);
	tmp->flag = flag;
	tmp->prc = prc;
	tmp->type = type;
	tmp->err_code = 0;
	tmp->last_red = 0;
	tmp->last_hdoc = 0;
	tmp->last_input = 0;
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

int	lstsize(t_pars *lst)
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
