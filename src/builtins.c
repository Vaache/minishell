/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:50:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/24 20:12:23 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(char *str, t_env_list *my_env)
{
	t_env_list	*tmp;
	char		buff[1024];
	int			i;
	char		**arr;

	if (ft_strncmp(str, ENV, ft_strlen(str)) == 0)
	{
		tmp = my_env;
		while (tmp != NULL)
		{
			if (tmp->flag == 0)
				ft_printf(1, "%s\n", tmp->line);
			tmp = tmp->next;
		}
	}
	if (ft_strncmp(str, "clear", ft_strlen(str)) == 0)
	{
		printf("\033[2J");
    	printf("\033[H");
	}
	if (ft_strncmp(str, "cd", 2) == 0)
	{
		pwd_init(my_env);
		arr = ft_split(str, ' ');
		if (!arr[1])
		{
			tmp = my_env;
			while (ft_strcmp(tmp->key, "HOME") != 0)
				tmp = tmp->next;
			chdir(tmp->data);
		}
		else if (chdir(arr[1]) != 0)
				ft_printf(1, "cd: no such file or directory: %s\n", arr[1]);
		tmp = my_env;
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->key, "PWD") == 0)
			{
				free(tmp->data);
				free(tmp->line);
				getcwd(buff, sizeof(buff));
				tmp->data = ft_strdup(buff);
				tmp->line = ft_strdup("");
				tmp->line = ft_strjoin(tmp->line, "PWD");
				tmp->line = ft_strjoin(tmp->line, "=");
				tmp->line = ft_strjoin(tmp->line, tmp->data);
				break ;
			}
			tmp = tmp->next;
		}
		free_2d(arr, strlen_2d(arr));
	}
	if (ft_strncmp(str, PWD, ft_strlen(PWD)) == 0)
	{

		if (getcwd(buff, sizeof(buff)) != NULL)
			printf("%s\n", buff);
		else
			perror("getcwd");
	}
	if (ft_strncmp(str, UNSET, ft_strlen(UNSET)) == 0)
	{
		arr = ft_split(str, ' ');
		i = 0;
		while (arr[++i])
		{
			arr[i] = ft_strtrim(arr[i], "\"");
			if (ft_strchr(arr[i], '"'))
				arr[i] = ft_strtrim(arr[i], "\"");
		}
		i = 0;
		while (arr && arr[++i])
			check_unset(arr[i], my_env);
		free_2d(arr, strlen_2d(arr));
	}
	builtins_2(str, my_env);
}

void	builtins_2(char *str, t_env_list *my_env)
{
	char		**arr;
	char		*s;
	long long	exit_num;
	(void)my_env;
	
	if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0)
	{
		arr = ft_split(str, ' ');
		exit_num = ft_atll(arr[1]);
		s = ft_itul(exit_num);
		if (arr[0] && arr[1] == NULL)
		{
			ft_printf(1, "exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (ft_strcmp(s, exit_num) == 0 && arr[1] != NULL)
		{
			ft_printf(2, "exit\n");
			exit (EXIT_FAILURE);
		}
	}
}