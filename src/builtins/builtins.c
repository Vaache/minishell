/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:50:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/06 13:43:11 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(char *str, t_env_list *my_env)
{
	t_env_list	*tmp;
	char		buff[1024];
	int			i;
	char		**arr;

	if (ft_strncmp(str, ENV, ft_strlen(ENV)) == 0)
	{
		tmp = my_env;
		while (tmp != NULL)
		{
			if (tmp->flag == 0)
				ft_printf(1, "%s\n", tmp->line);
			tmp = tmp->next;
		}
	}
	if (ft_strncmp(str, "clear", ft_strlen("clear")) == 0)
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
	char		*tmp;
	long long	exit_num;
	int			i;
	(void)my_env;
	
	s = NULL;
	i = 0;
	tmp = NULL;
	if (ft_strncmp(str, EXIT, ft_strlen(EXIT)) == 0)
	{
		arr = ft_split(str, ' ');
		if (arr[1] != NULL && (arr[1][0] == '0' || arr[1][0] == '+' || arr[1][1] == '0'))
			arr[1] = trim_zeroes(arr[1]);
		exit_num = ft_atll(arr[1]);
		s = ft_itul(exit_num);
		if (arr[1] && arr[1][0] == '+')
			s = ft_strjoin("+", s);
		if (strlen_2d(arr) == 1 && arr[1] == NULL)
		{
			ft_printf(1, "exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (strlen_2d(arr) == 2 && ft_strcmp(s, arr[1]) == 0)
		{
			ft_printf(2, "exit\n");
			if (exit_num == 0)
				exit (EXIT_SUCCESS);
			exit (exit_num % 256);
		}
		else if (ft_strlen(s) > 19 || check_digit(arr[1]) == 1 || ft_strcmp(s, arr[1]) != 0)
		{
			ft_printf(2, "exit\n");
			ft_printf(2, "Minishell: exit: %s: numeric argument required\n", arr[1]);
			exit(256);
		}
		else if (strlen_2d(arr) > 2 && check_digit(tmp) == 0)
		{
			ft_printf(1, "exit\n");
			ft_printf(1, "Minishell: exit: too many arguments\n");
		}
	}
	builtins_3(str);
	builtins_4(str, my_env);
}

void	builtins_3(char *str)
{
	char		**arr;
	
	if (ft_strncmp(str, "echo", 4) == 0)
	{
		int i = 1;
		int j = 1;
		arr = ft_split(str, ' ');
		if (arr[1] == NULL)
			ft_printf(1, "\n");
		if (arr[i] && ft_strncmp(arr[i], "-n", 2) == 0)
		{
			while (arr[i] != NULL && ft_strncmp(arr[i], "-n", 2) == 0)
			{
				j = 1;
				while (arr[i][j] && arr[i][j] == 'n')
					j++;
				if (arr[i][j] != '\0')
					break;
				else if (arr[i + 1] && ft_strncmp(arr[i + 1], "-n", 2) != 0)
				{
					while (arr[i + 1])
					{
						printf("%s", arr[i + 1]);
						if (arr[i + 2])
							printf(" ");
						i++;
						if (arr[i + 1] == NULL)
							return ;
					}
				}
				i++;
			}
			while (arr[i] && i != 1)
			{
				printf("%s", arr[i]);
				if (arr[i + 1])
					printf(" ");
				i++;
				if (arr[i] == NULL)
					return ;
			}
			
		}
		if(arr[i] && (ft_strncmp(arr[i], "-n", 2) != 0 || i == 1))
		{
			while (arr[i])
			{
				printf("%s", arr[i]);
				if (arr[i + 1])
					printf(" ");
				i++;
				if (arr[i] == NULL)
					printf("\n");
			}
		}
			
	}
}

void	builtins_4(char *str, t_env_list *my_env)
{
	char	**arr;
	t_env_list	*tmp;
	int	i;
	int	j;
	
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