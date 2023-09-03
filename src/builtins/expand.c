/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:19:02 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/08/31 17:23:25 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	onlydollar(char *str);

int	onlydollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

char	*expand(char *str, t_env **env)
{
	int		i;
	int		l ;
	t_env	*tmp;
	char	*s1;
	char	*s;

	i = -1;
	s = NULL;
	s1 = NULL;
	l = 0;
	if (onlydollar(str))
		return (ft_strdup(""));
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (i > 0 && !s)
			{
				s = ft_substr(str, 0, i);
			}
			else if (str[i + 1] != '\0')
			{
				s = ft_strjoin(s, ft_substr(str, l, i - l), 1);
			}
			i++;
			if (!ft_isalpha(str[i]) && str[i] != '?')
				s = ft_strjoin(s, "$", 1);
			l = i;
			while (str[l] != '\0' && str[l] != '$' && str[l] != ' ' && str[l] != '\'')
				l++;
			tmp = (*env);
			s1 = ft_substr(str + i, 0, l - i);
			while (tmp)
			{
				if (str[i] == '?')
				{
					if (!ft_strcmp(tmp->key, "$?"))
						s = ft_strjoin(s, tmp->data, 1);
				}
				else if (l - i != 0 && !ft_strcmp(s1, tmp->key))
					s = ft_strjoin(s, tmp->data, 1);
				tmp = tmp->next;
			}
			free(s1);
		}
		if (!ft_strchr(str + l, '$'))
		{
			i = l;
			s = ft_strjoin(s, str + i, 1);
			break;
		}
	}
	return (s);
}