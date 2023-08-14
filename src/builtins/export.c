/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:33:14 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/08/14 12:45:28 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_export(char *str, t_env *my_env);
void	ft_export(t_env *my_env);
int		ft_check(t_env *my_env, char *str);
void	ft_add(t_env *my_env, char *str);

void	minishell_export(char *str, t_env *my_env)
{
	char		**arr;
	t_env	*tmp;
	int			i;
	int			j;

	i = 1;
	j = 0;
	tmp = my_env;
	if (ft_strncmp(str, "export", 6) == 0)
	{
		arr = ft_split(str, ' ');
		if (arr[1] == NULL)
		{
			ft_export(my_env);
			return ;
		}
		while (arr[i])
		{
			if (ft_strchr(arr[i], '=') != 0)
			{
				if (ft_check(my_env, arr[i]) == 0)
					tmp = push_back(&tmp, malloc_list(arr[i]));
				else
					ft_add(my_env, arr[i]);
			}
			else
			{
				if (ft_check(my_env, arr[i]) == 0)
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
}

void	ft_export(t_env *my_env)
{
	t_env	*tmp;
	t_env	*tmp2;
	int			flag;

	tmp = my_env;
	tmp2 = my_env;
	flag = 0;
	while (tmp)
	{
		if (tmp->flag == 0)
		{
			printf("declare -x ");
			printf("%s%c\"%s\"\n", tmp->key, '=', tmp->data);
		}
		if (tmp->flag == 2)
		{
			printf("declare -x ");
			printf("%s\n", tmp->key);
		}
		tmp = tmp->next;
	}
	while (tmp2)
	{
		if (ft_strcmp(tmp2->key, "OLDPWD") == 0)
		{
			flag = 1;
			break ;
		}
		tmp2 = tmp2->next;
	}
	if (flag == 0)
		printf("declare -x OLDPWD\n");
}

int	ft_check(t_env *my_env, char *str)
{
	t_env	*tmp;
	int			i;

	tmp = my_env;
	i = 0;
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		ft_printf(2, "Minishell: export: `%s': not a valid identifier\n", str);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
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
	int			i;

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
			free(tmp->line);
			tmp->line = ft_strdup("");
			tmp->data = ft_strdup(str + i + 1);
			tmp->line = ft_strjoin(tmp->line, tmp->key, 1);
			tmp->line = ft_strjoin(tmp->line, "=", 1);
			tmp->line = ft_strjoin(tmp->line, tmp->data, 1);
			tmp->flag = 0;
		}
		tmp = tmp->next;
	}
}
