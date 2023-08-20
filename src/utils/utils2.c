/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:53:27 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/20 13:04:02 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_mode(char *s1, char *s2, int mode);
char	*trim_zeroes(char *s);
char	*search_redir(char *str);
int		error_code(int error_num);
void	update_shlvl(t_env **env);

char	*trim_zeroes(char *s)
{
	int		j;
	char	*str;

	j = 0;
	str = NULL;
	if (s[j] == '-' || s[j] == '+')
		j++;
	if (s[j] == '0' || (s[j] == '0' && s[j + 1] == '0'))
	{
		while (s && s[j] != '\0')
		{
			while (s[j] != '\0' && s[j] == '0')
				j++;
			if (s[j] != '0')
				break ;
		}
		if (s[j] != '\0' && s[j] != '0')
			str = (char *)malloc(sizeof(char) * (j + 1));
		if (!str)
			return (NULL);
		str = ft_strdup(&s[j]);
		return (str);
	}
	return (s);
}

char	*strjoin_mode(char *s1, char *s2, int mode)
{
	if (mode == 1)
		s1 = ft_strjoin(s1, "\n", 1);
	else
		s1 = ft_strjoin(s1, " ", 1);
	s1 = ft_strjoin(s1, s2, 1);
	return (s1);
}

char	*search_redir(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
			break ;
		if (str[i] && str[i + 1] && ((str[i] == '&' && str[i + 1] == '&') || \
			(str[i] == '|' && str[i + 1] == '|') || \
			(str[i] == '<' && str[i + 1] == '<') || \
			(str[i] == '>' && str[i + 1] == '>')))
		{
			tmp = ft_substr(str + i, 0, 2);
			return (tmp);
		}
		else if (str[i] && (str[i] == '&' || str[i] == '|' || \
			str[i] == '<' || str[i] == '>'))
		{
			tmp = ft_substr(str + i, 0, 1);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

int	error_code(int error_num)
{
	if (error_num == 256)
		return (1);
	return (error_num % 256);
}

void	update_shlvl(t_env **env)
{
	t_env	*tmp;
	char	*str;

	tmp = (*env);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL"))
		{
			str = ft_itoa(ft_atoi(tmp->data) + 1);
			free(tmp->data);
			tmp->data = ft_strdup(str);
			if (ft_atoi(tmp->data) > 1000)
			{
				ft_printf(2, "Minishell: warning: shell level (%s) %s\n", \
					tmp->data, "too high, resetting to 1");
				free(tmp->data);
				tmp->data = ft_strdup("1");
			}
			free(str);
			break ;
		}
		tmp = tmp->next;
	}
}
