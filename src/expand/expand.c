/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:19:02 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/09/08 17:09:48 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		onlydollar(char *str);
void	exp_1(t_exp **tmp);
void	exp_2(t_exp **tmp, t_env **env);
void	exp_3(t_exp **tmp);
char	*expand(char *str, t_env **env, t_exp *exp);

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

void	exp_1(t_exp **tmp)
{
	t_exp	*exp;
	char	*s1;

	s1 = NULL;
	exp = (*tmp);
	if (exp->i > 0 && !exp->s)
		exp->s = ft_substr(exp->str, 0, exp->i);
	else if (exp->str[exp->i + 1] != '\0')
	{
		s1 = ft_substr(exp->str, exp->l, exp->i - exp->l);
		exp->s = ft_strjoin(exp->s, s1, 1);
		free(s1);
	}
	exp->i++;
	if (!ft_isalpha(exp->str[exp->i]) && exp->str[exp->i] != '?')
		exp->s = ft_strjoin(exp->s, "$", 1);
	exp->l = exp->i;
	while (exp->str[exp->l] != '\0' && exp->str[exp->l] != '$' && \
			exp->str[exp->l] != ' ' && exp->str[exp->l] != '\'' && \
			exp->str[exp->l] != '=' && exp->str[exp->l] != '\n')
		exp->l++;
}

void	exp_2(t_exp **tmp, t_env **env)
{
	t_exp	*exp;
	char	*s1;
	t_env	*tmp_env;

	exp = *tmp;
	s1 = NULL;
	s1 = ft_substr(exp->str + exp->i, 0, exp->l - exp->i);
	tmp_env = (*env);
	while (tmp_env)
	{
		if (exp->str[exp->i] == '?')
		{
			if (!ft_strcmp(tmp_env->key, "$?"))
				exp->s = ft_strjoin(exp->s, tmp_env->data, 1);
		}
		else if (exp->l - exp->i != 0 && !ft_strcmp(s1, tmp_env->key))
			exp->s = ft_strjoin(exp->s, tmp_env->data, 1);
		tmp_env = tmp_env->next;
	}
	exp->i = exp->l;
	free(s1);
}

void	exp_3(t_exp **tmp)
{
	t_exp	*exp;
	char	*s1;

	s1 = NULL;
	exp = *tmp;
	exp->i = exp->l;
	while (exp->str[exp->l] && exp->str[exp->l] != '$')
		exp->l++;
	s1 = ft_substr(exp->str, exp->i, exp->l - exp->i);
	exp->s = ft_strjoin(exp->s, s1, 1);
	free(s1);
	exp->i = exp->l - 1;
}

char	*expand(char *str, t_env **env, t_exp *exp)
{
	char	*s1;

	s1 = NULL;
	exp->str = ft_strdup(str);
	if (onlydollar(exp->str))
		return ("$");
	while (exp->str[++exp->i])
	{
		if (exp->str[exp->i] == '$')
		{
			exp_1(&exp);
			exp_2(&exp, env);
		}
		if (!ft_strchr(exp->str + exp->l, '$'))
		{
			exp->s = ft_strjoin(exp->s, exp->str + exp->i, 1);
			break ;
		}
		else if (exp->str[exp->i] != '$')
			exp_3(&exp);
	}
	return (exp->s);
}
