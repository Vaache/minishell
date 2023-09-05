/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:24:32 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/05 18:18:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_2(t_main *main, t_env *my_env);

int	main(int ac, char **av, char **env)
{
	t_env		*my_env;
	t_main		main;

	if (ac != 1 || av[1] != NULL)
	{
		ft_printf(2, "%s", "Error\n");
		return (1);
	}
	my_env = NULL;
	main_init(&main);
	print_header();
	call_signals();
	my_env = env_init(env, my_env);
	main_2(&main, my_env);
	return (0);
}

void	main_2(t_main *main, t_env *my_env)
{
	char	*str;

	init_hd(&main->hd);
	while (1)
	{
		save_backup(&main);
		str = readline("Minishell 4.2% ");
		if (str == NULL)
		{
			ft_printf(1, "exit\n");
			break ;
		}
		if (str && *str)
			add_history(str);
		if (onlyspace(str) == 1)
		{
			lex(str, main, &my_env);
			if (main->pars)
			{
				check_astree(main, main->pars, &my_env);
				destroy_main(main);
			}
		}
		free(str);
	}
}
