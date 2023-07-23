/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:24:32 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/23 16:46:13 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int ac, char **av, char **env)
{
	char		*str;
	int			i;
	t_env_list	*my_env;

	if (ac != 1 || av[1])
	{
		printf("Error\n");
		return (1);
	}
	my_env = NULL;
	print_header();
	call_signals();
	my_env = env_init(env, my_env);
	i = -1;
	while (1)
	{
		str = readline("Minishell 4.2% ");
		if (str == NULL)
		{
			free(str);
			break ;
		}
		add_history(str);
		builtins(str, my_env);
		free(str);
	}
	return (0);
}
