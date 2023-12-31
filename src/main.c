/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:24:32 by vhovhann          #+#    #+#             */
/*   Updated: 2023/12/04 18:26:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_2(t_shell *main, t_env *my_env, char *str);

int	main(int ac, char **av, char **env)
{
	t_env		*my_env;
	t_shell		main;

	if (ac != 1 || av[1] != NULL)
	{
		ft_printf(2, "%s", "Error\n");
		return (1);
	}
	my_env = NULL;
	main_init(&main);
	print_header();
	my_env = env_init(env, my_env);
	init_hd(&main.hd);
	rl_catch_signals = 0;
	main_2(&main, my_env, NULL);
	return (0);
}

void	main_2(t_shell *main, t_env *my_env, char *str)
{
	while (1)
	{
		run_signals(1);
		save_backup(&main);
		str = readline("Minishell 4.2% ");
		if (str == NULL)
		{
			write(2, "exit\n", 5);
			if (g_exit_status_ == 130)
				exit(1);
			exit(main->exit_status);
		}
		if (onlyspace(str))
		{
			lex(&str, main, my_env);
			if (main->pars)
			{
				main->exit_status = check_astree(main, main->pars, my_env);
				destroy_main(main);
			}
			handle_dollar(main->exit_status, &my_env);
		}
		add_history(str);
		free(str);
	}
}
