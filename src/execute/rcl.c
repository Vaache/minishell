/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:19:34 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/27 22:45:40 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**restore_cmd_line(t_pars *stack, int i);
void	fill_wcard(t_pars *stack, t_wcard **wcard);
char	**malloc_2d_wc(char **arr, t_pars *stack, t_wcard **wcard);
char	**fill_cmd_matrix(char **arr, char *str, t_wcard *wild, int *i);

char	**restore_cmd_line(t_pars *stack, int i)
{
	char		**cmd_matrix;
	int			mode;
	t_pars		*tmp;
	t_wcard		*wcard;

	wcard = NULL;
	cmd_matrix = NULL;
	cmd_matrix = malloc_2d_wc(cmd_matrix, stack, &wcard);
	tmp = stack;
	while (tmp && tmp->cmd)
	{
		mode = ((tmp->flag & (1 << 1)) && 1);
		if (mode == 0 && check_types(tmp->type) == 0)
		{
			if (i < 0)
				i++;
			cmd_matrix[i] = ft_strjoin(cmd_matrix[i], tmp->cmd, 1);
		}
		else
			cmd_matrix = fill_cmd_matrix(cmd_matrix, tmp->cmd, wcard, &i);
		tmp = tmp->next;
	}
	lstclear_wcard(&wcard);
	return (cmd_matrix);
}



char	**malloc_2d_wc(char **arr, t_pars *stack, t_wcard **wcard)
{
	int		i;

	i = 0;
	fill_wcard(stack, wcard);
	if (*wcard)
		arr = (char **)malloc(sizeof(char *) * (lstsize(stack) + lstsize_wcard((*wcard))));
	else
		arr = (char **)malloc(sizeof(char *) * (lstsize(stack) + 1));
	if (!arr)
		return (NULL);
	if (*wcard)
		while (i < lstsize(stack) + lstsize_wcard((*wcard)) - 1)
			arr[i++] = NULL;
	else
		while (i < lstsize(stack))
			arr[i++] = NULL;
	arr[i] = NULL;
	return (arr);
}

char	**fill_cmd_matrix(char **arr, char *str, t_wcard *wild, int *i)
{
	t_wcard	*tmp_wc;

	tmp_wc = wild;
	if (tmp_wc && ft_strchr(str, '*'))
	{
		while (tmp_wc)
		{
			*i += 1;
			arr[*i] = ft_strdup(tmp_wc->file);
			tmp_wc = tmp_wc->next;
		}
	}
	else
	{
		*i += 1;
		arr[*i] = ft_strdup(str);
	}
	return (arr);
}

void	fill_wcard(t_pars *stack, t_wcard **wcard)
{
	t_pars	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (tmp->type == DQUOTE || tmp->type == SQUOTE)
			tmp = tmp->next;
		else if (ft_strchr(tmp->cmd, '*'))
		{
				get_file(tmp->cmd, wcard);
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}