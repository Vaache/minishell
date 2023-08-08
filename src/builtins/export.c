/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:33:14 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/08/08 12:20:21 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_env_list *my_env)
{
	t_env_list	*tmp;
	t_env_list	*tmp2;
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

int	ft_check(t_env_list *my_env, char *str)
{
	t_env_list	*tmp;
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

void	ft_add(t_env_list *my_env, char *str)
{
	t_env_list	*tmp;
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
