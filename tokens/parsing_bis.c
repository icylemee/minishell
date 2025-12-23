/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:29:36 by mlemee            #+#    #+#             */
/*   Updated: 2025/12/08 21:56:10 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_fill_word_quote(char *line)
{
	char	*word;

	word = NULL;
	if (line[0] == SING_QUOTE_D)
		word = ft_fill_word_which_q(line, word, SING_QUOTE_D);
	if (line[0] == DOUB_QUOTE_D)
		word = ft_fill_word_which_q(line, word, DOUB_QUOTE_D);
	if (!word)
		return (NULL);
	return (word);
}

char	*ft_fill_word(char *line)
{
	int		i;
	int		len;
	char	*word;

	i = -1;
	len = 0;
	while (line[++i] && ft_check_quote(line[i]) == 0
		&& ft_check_redir_n_pipe(&line[i]) == WORD && line[i] != ' '
		&& line[i] != '\t')
		len ++;
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		return (error_malloc(), NULL);
	i = -1;
	while (++i < len)
		word[i] = line[i];
	word[i] = 0;
	return (word);
}

int	ft_check_redir_n_pipe(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '|')
		return (PIPE);
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (HEREDOC);
		return (REDIR_IN);
	}
	if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			return (REDIR_D_OUT);
		return (REDIR_OUT);
	}
	return (WORD);
}

char	*ft_fill_word_pipe_n_redir(char *line, t_token_type type)
{
	char	*word;

	if (type == HEREDOC || type == REDIR_D_OUT)
	{
		word = malloc(sizeof(char) * 2 + 1);
		if (!word)
			return (error_malloc(), NULL);
		ft_strlcpy(word, line, 3);
		return (word);
	}
	else
	{
		word = malloc(sizeof(char) * 1 + 1);
		if (!word)
			return (error_malloc(), NULL);
		ft_strlcpy(word, line, 2);
		return (word);
	}
	return (NULL);
}

t_quote_state	ft_quote_state(char c)
{
	if (c == SING_QUOTE_D)
		return (SINGLE_QUOTE_T);
	if (c == DOUB_QUOTE_D)
		return (DOUBLE_QUOTE_T);
	return (NO_QUOTE_T);
}