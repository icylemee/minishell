/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:37:49 by mlemee            #+#    #+#             */
/*   Updated: 2025/12/08 21:19:17 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	error_malloc(void)
{
	ft_putendl_fd("minishell: malloc: cannot allocate enough bytes", 2);
	write(2, "\n", 1);
}

void	ft_lstclear_token(t_token **lst)
{
	t_token	*current;
	t_token	*next_node;

	if (!lst)
		return ;

	current = *lst;
	while (current)
	{
		next_node = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next_node;
	}
	*lst = NULL;
}
