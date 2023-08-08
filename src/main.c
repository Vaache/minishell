/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:24:32 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/09 00:33:06 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_env_list	*my_env;
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
	main.exit_status = 0;
	my_env = env_init(env, my_env);
	print_header();
	call_signals();
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
		if (onlyspace(str) == 1)
		{
			lex(str, &main);
		}
		builtins(str, my_env);
		free(str);
	}
	system("leaks minishell");
	return (0);
}
