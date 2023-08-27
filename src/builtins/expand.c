/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:34:27 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/08/18 21:06:13 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *str, t_env *my_env);

char	*expand(char *str, t_env *my_env)
{
	int			i;
	int			j;
	int			l;
	char		**arr;
	char		*new;
	t_env		*tmp;
	char		*s;
	char		**arr2;
	
	i = -1;
	new = NULL;
	s = NULL;
	if (!str)
		return (NULL);
	arr = ft_split(str, ' ');
	if (!arr)
		return (NULL);
	if (ft_strchr(str, '$'))
	{
		while (arr[++i])
		{
			j = -1;
			tmp = my_env;
			if (arr[i][j + 1] == '"')
				arr[i] = ft_strtrim(arr[i], "\"");
			while (arr[i][++j])
			{
				if (arr[i][j] == '$')
				{
					if (j > 0)
						s = ft_substr(arr[i], 0, j);
					j++;
					l = ft_strlen(arr[i]);
					if (ft_strchr(arr[i] + j, '$'))
					{
						l = j;
						while (arr[i][l] != '$' && arr[i][l] && arr[i][l] != ' ')
							l++;
					}
					else
						while (arr[i][l - 1] == ' ' && l)
							l--;
					while (tmp)
					{
						if (!ft_strncmp(arr[i] + j, tmp->key, l - j))
						{
							if (arr[i][ft_strlen(arr[i]) - 1] == ' ')
							{
								arr[i] = ft_strjoin(ft_strjoin(s, tmp->data, 1),
									ft_substr(arr[i], l + 1, ft_strlen(arr[i]) - l + 1), 1);
							}
							else
							{
								arr[i] = ft_strjoin(ft_strjoin(s, tmp->data, 1),
									ft_substr(arr[i], l, ft_strlen(arr[i]) - l), -1);
							}
							break ;
						}
						tmp = tmp->next;
					}
					if (!tmp && (size_t)l < ft_strlen(arr[i]))
					{
						arr[i] = ft_strdup(arr[i] + l);
						j = -1;
						tmp = my_env;
					}
					else if (!tmp && s)
					{
						arr[i] = ft_strdup(s);
						j = ft_strlen(arr[i]) - 1;
					}
					else if (tmp && arr[i][l])
					{
						j = -1;
						tmp = my_env;
					}
				}
			}
			s = NULL;
		}
		i = -1;
		arr2 = ft_split(str, ' ');
		while (arr[++i])
		{
			if (ft_strchr(arr[i], '$') == 0)
			{
				if (arr2[i][0] == '\"' && arr2[i][ft_strlen(arr2[i]) - 1] == '\"')
				{
					new[ft_strlen(new)] = '\"';
					new = ft_strjoin(new, arr[i], -1);
					new = ft_strjoin(new, "\"", -1);
				}
				else
					new = ft_strjoin(new, arr[i], -1);
				if (arr[i + 1])
					new = ft_strjoin(new, " ", -1);
			}
		}
		str = ft_strdup(new);
	}
	free_2d(arr);
	return (str);
}