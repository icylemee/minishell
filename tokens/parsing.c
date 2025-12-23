/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:14:29 by mlemee            #+#    #+#             */
/*   Updated: 2025/12/08 22:11:44 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_quote(char c)
{
	if (c == SING_QUOTE_D || c == DOUB_QUOTE_D)
		return (c);
	return (0);
}

char	*ft_fill_word_which_q(char *line, char *word, int quote)
{
	int	len;
	int	i;

	len = 0;
	i = 0; // on commence a 0 pour jump la quote du debut qui est de sur la
	while (line[++i] && line[i] != quote)
		len++;
	if (line[i] == 0)
	{
		// gerer le cas quand une quote ouverte nest pas fermee
		return (ft_putendl_fd("syntax error: unclosed quote", 0), NULL);
	}
	word = malloc(sizeof(char) * len + 3); // +2 pour la quote plus carac de fin et +1 pour la quote du debut quon a jump
	if (!word)
		return (NULL);
	i = -1;
	while (++i < len + 2) // len + 2 pour la quote de debut et de fin
		word[i] = line[i];
	word[i] = 0;
	return (word);
}

t_token	*ft_create_list_tokens(char *line)
{
	t_token			*start;
	char			*word;
	t_token_type	type;
	t_quote_state	quote_state;
	int				i;

	i = 0;
	start = NULL;
	word = NULL;
	while (line[i])
	{
		quote_state = NO_QUOTE_T;
		type = WORD;
		while (line[i] == ' ')
			i++;
		if (line[i] == 0)
			break ;
		if (ft_check_quote(line[i]) != 0)
		{
			word = ft_fill_word_quote(&line[i]);
			quote_state = ft_quote_state(line[i]);
		}
		else if (ft_check_redir_n_pipe(&line[i]) != WORD)
		{
			type = ft_check_redir_n_pipe(&line[i]);
			word = ft_fill_word_pipe_n_redir(&line[i], type);
		}
		else
			word = ft_fill_word(&line[i]);
		if (!word)
			return (ft_lstclear_token(&start), NULL);
		if (!ft_append_token(&start, word, type, quote_state))
		{
			free(word); // On free le mot car il n'est pas dans la liste
			return (ft_lstclear_token(&start), NULL);
		}
		i += ft_strlen(word);
		free(word);
	}
	return (start);
}

int	ft_append_token(t_token **start, char *word,
	t_token_type type, t_quote_state state)
{
	t_token	*new_token;

	new_token = ft_create_token(word, type, state);
	if (!new_token)
		return (0);
	ft_lstadd_back_tok(start, new_token);
	return (1);
}

t_token	*ft_create_token(char *word, t_token_type type, t_quote_state state)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (error_malloc(), NULL);
	new->content = ft_strdup(word);
	if (!new->content)
		return (free(new), NULL);
	new->type = type;
	new->state = state;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
