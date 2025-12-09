/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 22:25:54 by mlemee            #+#    #+#             */
/*   Updated: 2025/12/09 21:09:19 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *key, t_env2 *env)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(key, env->key_env) == 0)
			return (env->value_env);
		env = env->next;
	}
	return (NULL);
}


// Étape B : Le remplacement pur (get_var_value) 🧪

// On va créer une fonction qui prend juste un mot (ex: "$USER") et 
//renvoie sa traduction ("mlemee"). Elle devra gérer le cas spécial $?.

//     Temps estimé : 30 min
char	*ft_get_var_value(char *key, t_env2 *env)
{
	char	*val;

	if (!env || !key)
		return (NULL);
	if (ft_strcmp(key, "?") == 0)
		return (ft_strdup("0")); // a chamger plus tard, il faudra mettre par un iota(g_exit_status)
	val = ft_getenv(key, env);
	if (val)
		return (ft_strdup(val));
	return (ft_strdup(""));
}

//etape C ; extraction de la cle
// foction util 
/*
** Renvoie la longueur du nom de la variable.
** Ex: str = "USER, ca va ?" -> renvoie 4 (pour U, S, E, R)
** Ex: str = "?..." -> renvoie 1
*/

int	ft_isalnum(int c)
{
	if (!((c >= '0' && c <= '9')
			|| (c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z' )))
		return (0);
	return (1);
}
int	ft_var_len(char *str)
{
	int	i;

	i = 0;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '?')
		return (1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_' )
			i++;
		else
			return (i);
	}
	return (i);
}

char	*ft_fill_new_after_expand(t_token *token, t_env2 *env, int len)
{
	char	*new;
	char	*key;
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (error_malloc(), NULL);
	while (token->content[i])
	{
		if (token->content[i] == '$')
		{
			i++;
			key = ft_fill_key_expand(&token->content[i],ft_var_len(&token->content[i]));
			if (!key)
				return (NULL);
			val = ft_get_var_value(key, env);
			if (!val)
				return (NULL);
			ft_strlcpy(&new[j], val, ft_strlen(val) + 1);
			i += ft_var_len(&token->content[i]);
			j += ft_strlen(val);
			free(key);
			free(val);
		}
		else
		{
			new[j] = token->content[i];
			i++;
			j++;
		}
	}
	new[j] = 0;
	return (new);
}

char	*ft_fill_key_expand(char *str, int len)
{
	char	*key;

	key = malloc(sizeof(char) * len + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, str, len + 1);
	return (key);
}

int	ft_is_key(char c)
{
	if (ft_isalnum(c) == 1)
		return (1);
	if (c == '_' || c == '?')
		return (1);
	return (0);
}

int	ft_expand_token(t_token	*token, t_env2	*env)
{
	int		i;
	int		len;
	char	*key;
	char	*new;
	char	*val;

	i = 0;
	len = 0;
	if (!token || !env)
		return (0);
	if (token->content == NULL)
		return (0);
	while (token->content[i])
	{
		if (token->content[i] == '$' && token->state != SINGLE_QUOTE_T
			&& (ft_is_key(token->content[i + 1])))
		{
			i++;
			key = ft_fill_key_expand(&token->content[i], ft_var_len(&token->content[i]));
			if (!key)
				return (0);
			val = ft_get_var_value(key, env);
			if (!val)
				return (0);
			len += ft_strlen(val);
			i += ft_var_len(&token->content[i]);
			free(key);
			free(val);
		}
		else
		{
			i++;
			len++;
		}
	}
	new = ft_fill_new_after_expand(token, env, len);
	if (!new)
		return (0);
	free(token->content);
	token->content = new;
	return (1);
}



