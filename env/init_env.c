/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:40:00 by mlemee            #+#    #+#             */
/*   Updated: 2025/12/08 21:53:26 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env2	*ft_init_node_env(char *env)
{
	t_env2	*tab_env2;

	tab_env2 = malloc(sizeof(t_env2));
	if (!tab_env2)
		return (NULL);
	tab_env2->key_env = ft_extract_key_env(env);
	if (!tab_env2->key_env)
		return (free(tab_env2), NULL);
	tab_env2->value_env = ft_extract_value_env(env);
	if (!tab_env2->value_env)
		return (free(tab_env2->key_env), free(tab_env2), NULL);
	tab_env2->next = NULL;
	return (tab_env2);
}

char	*ft_extract_value_env(char *str)
{
	int		i;
	int		index_egal;
	int		len_value_env;
	char	*value_env;

	i = 0;
	index_egal = ft_strlen_key_env(str);
	if (index_egal == -1)
		return (printf("ERREUR '=' PAS TROUVE DANS LA STR D'ENV\n"), NULL);
	len_value_env = ft_strlen_value_env(index_egal, str);
	value_env = malloc(sizeof(char) * len_value_env + 1);
	if (!value_env)
		return (error_malloc(), NULL);
	index_egal++;
	while (i < len_value_env)
	{
		value_env[i] = str[index_egal];
		i++;
		index_egal++;
	}
	value_env[len_value_env] = '\0';
	return (value_env);
}

int	ft_strlen_value_env(int index_egal, char *str)
{
	int	count;

	index_egal++; // car cest lindex ou il y a le '=';
	count = 0;
	while (str[index_egal])
	{
		index_egal++;
		count++;
	}
	return (count);
}

char	*ft_extract_key_env(char *str)
{
	int		i;
	int		index_egal;
	char	*key_env;

	i = 0;
	index_egal = ft_strlen_key_env(str);
	if (index_egal == -1)
		return (printf("ERREUR '=' PAS TROUVE DANS LA STR D'ENV\n"), NULL);
	key_env = malloc(sizeof(char) * index_egal + 1);
	if (!key_env)
		return (error_malloc(), NULL);
	while (i < index_egal)
	{
		key_env[i] = str[i];
		i++;
	}
	key_env[index_egal] = '\0';
	return (key_env);
}

int	ft_strlen_key_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}