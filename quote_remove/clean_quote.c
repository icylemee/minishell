#include "minishell.h"


int	ft_remove_quote(t_token **token)
{
	t_token 	*current;
	char		*tmp;

	if (!token || !*token)
		return (1);
	current = *token;
	tmp = NULL;
	while (current)
	{ 
		if (current->state == SINGLE_QUOTE_T || current->state == DOUBLE_QUOTE_T)
		{
			tmp = ft_substr(current->content, 1, (ft_strlen(current->content) - 2));
			if (!tmp)
				return (-1);
			free(current->content);
			current->content = tmp;
			current->state = NO_QUOTE_T;
		}
		current = current->next;
	}
	return (1);
}
