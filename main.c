/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:48:25 by mlemee            #+#    #+#             */
/*   Updated: 2025/12/09 17:09:49 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>


// Petite fonction de test remplissage env
void	print_env_list(t_env2 *env)
{
	while (env)
	{
		printf("KEY: %s | VALUE: %s\n", env->key_env, env->value_env);
		env = env->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env2	*my_env;
	t_token	*tokens;

	(void)argc;
	(void)argv;

	// pour tester le remplissage de l'env
	my_env = ft_create_list_env(env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	print_env_list(my_env);

	while (1)
	{
		if (g_signal != 0)
		{
			// Code de mise à jour du $? à faire plus tard
			g_signal = 0;
		}
		line = readline("Minishell : ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line[0] != '\0')
			add_history(line);
		tokens = ft_create_list_tokens(line);
		if (!tokens)
			return (-1);
		printf("Jai ecrit : %s\n", line);
		free(line);
	}
}

t_env2	*ft_create_list_env(char **env)
{
	t_env2	*last_node;
	t_env2	*start;
	t_env2	*new;
	int		i;

	i = 0;
	start = ft_init_node_env(env[i]);
	if (!start)
		return (NULL);
	last_node = start;
	i = 1;
	while (env[i])
	{
		new = ft_init_node_env(env[i]);
		if (!new)
			return (ft_lstclear(&start, del_node_env), NULL);
		last_node->next = new;
		last_node = new;
		i++;
	}
	return (start);
}




