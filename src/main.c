/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:24:32 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/29 14:43:11 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_env		*my_env;
	t_main		main;

	if (ac != 1 || av[1] != NULL)
	{
		ft_printf(2, "%s", "Error\n");
		return (1);
	}
	my_env = NULL;
	main.lex = NULL;
	main.pars = NULL;
	main.temp = NULL;
	main.path = NULL;
	main.flag = 1;
	main.hdoc = 0;
	main.redir = 0;
	main.exit_status = 0;
	print_header();
	call_signals();
	my_env = env_init(env, my_env);
	while (1)
	{
		str = readline("Minishell 4.2% ");
		if (str == NULL)
		{
			free(str);
			break ;
		}
		if (str && *str)
			add_history(str);
		str = expand(str, my_env);
		if (onlyspace(str) == 1)
		{
			lex(str, &main);
			if (main.pars)
			{
				check_astree(&main, main.pars, &my_env);
				destroy_main(&main);
			}
		}
		free(str);
		// system("leaks minishell");
		
	}
	return (0);
}
