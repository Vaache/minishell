/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:33:14 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/08/25 17:18:23 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_export(char **arr, t_env **my_env);
void	ft_export(t_env *my_env);
int		ft_check(t_env *my_env, char *str);
void	ft_add(t_env *my_env, char *str);

void	minishell_export(char **arr, t_env **my_env)
{
	t_env	*tmp;
	int		i;

	i = 1;
	tmp = (*my_env);
	if (arr[1] == NULL)
	{
		ft_export((*my_env));
		return ;
	}
	if (ft_check((*my_env), arr[i]) == 2)
		return ;
	while (arr[i])
	{
		if (ft_strchr(arr[i], '=') != 0)
		{
			if (ft_check((*my_env), arr[i]) == 0)
				tmp = push_back(&tmp, malloc_list(arr[i]));
			else
				ft_add((*my_env), arr[i]);
		}
		else
		{
			if (ft_check((*my_env), arr[i]) == 0)
			{
				tmp = push_back(&tmp, malloc_list(arr[i]));
				while (tmp->next)
					tmp = tmp->next;
				tmp->flag = 2;
			}
		}
		i++;
	}
}

void	ft_export(t_env *my_env)
{
	t_env	*tmp;
	int		flag;

	tmp = my_env;
	flag = 0;
	while (tmp)
	{
		if (tmp->flag == 0)
			ft_printf(1, "declare -x %s%c\"%s\"\n", tmp->key, '=', tmp->data);
		if (tmp->flag == 2)
			ft_printf(1, "declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	tmp = my_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (flag == 0)
		ft_printf(1, "declare -x OLDPWD\n");
}

int	ft_check(t_env *my_env, char *str)
{
	t_env	*tmp;
	int		i;

	tmp = my_env;
	i = -1;
	while (str && str[++i])
	{
		if (str[0] != '=' && str[i] == '=')
			break ;
		if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		{
			ft_printf(2, "Minishell: export: `%s': not a %s\n", \
					str, "valid identifier");
			return (2);
		}
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->key, str, i) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_add(t_env *my_env, char *str)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = my_env;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->key, str, i) == 0)
		{
			free(tmp->data);
			tmp->data = ft_strdup(str + i + 1);
			tmp->flag = 0;
		}
		tmp = tmp->next;
	}
}
