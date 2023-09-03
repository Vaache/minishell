/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:19:02 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/09/03 18:49:42 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		onlydollar(char *str);
void	call_expand(t_tok *stack, t_env *env);
char	*expand(char *str, t_env **env);

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
				s1 = ft_substr(str, l, i - l);
				s = ft_strjoin(s, s1, 1);
				free(s1);
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
			i = l;
			free(s1);
		}
		if (!ft_strchr(str + l, '$'))
		{
			s = ft_strjoin(s, str + i, 1);
			break;
		}
		else if (str[i] != '$')
		{
			i = l;
			while (str[l] && str[l] != '$')
				l++;
			s1 = ft_substr(str, i, l - i);
			s = ft_strjoin(s, s1, 1);
			free(s1);
			i = l - 1;
		}
	}
	return (s);
}

void	call_expand(t_tok *stack, t_env *env)
{
	t_tok	*tmp;
	char	*str;

	tmp = stack;
	while (tmp)
	{
		if (ft_strchr(tmp->cmd, '$') && tmp->type != SQUOTE)
		{
			str = expand(tmp->cmd, &env);
			free(tmp->cmd);
			tmp->cmd = ft_strdup(str);
			free(str);
		}
		tmp = tmp->next;
	}
}