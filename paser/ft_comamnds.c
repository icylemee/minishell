
#include "minishell.h"

int	ft_count_args(t_token *token)
{
	t_token	*current;
	int		args;

	if (!token)
		return (0);
	current = token;
	args = 0;
	while (current && current->type == WORD)
	{
		current = current->next;
		args ++;
	}
	return (args);
}

int	ft_len_juska_pipe(t_token *token)
{
	t_token	*current;
	int		len;

	if (!token)
		return (0);
	current = token;
	len = 0;
	while (current && current->type != PIPE)
	{
		current = current->next;
		len ++;
	}
	return (len);
}

t_cmd	*ft_init_new_cmd(int count_args)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = malloc(sizeof(char *) * count_args + 1);
	if (!new->cmd)
		return (NULL);
	new->next = NULL;
	new->redir = NULL;
	new->pid = 0;
	return (new);
}

char	*ft_fill_string(char *src)
{
	char	*str;
	int		len;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	len = ft_strlen(src);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = src[i];
		i ++;
	}
	str[i] = '\0';
	return (str);
}

t_redir	*ft_fill_redir_cmd(t_token **token)
{
	t_redir	*start;
	t_redir	*new;
	t_token	*cpy;

	if (!token || !*token)
		return (NULL);
	cpy = *token;
	start = malloc(sizeof(t_redir));
	if (!start)
		return (NULL);
	start->type = cpy->type;
	cpy = cpy->next;
	start->path = ft_fill_string(cpy->content);
	if (start->path == NULL)
		return (NULL);
	start->next = NULL;
	if (cpy->next)
		cpy = cpy->next;
	while (cpy && cpy->type != PIPE)
	{
		new = ft_create_node_redir(cpy);
		if (!new)
			return (NULL);
		// faire fonction fill du new node ou gerer daNS FT CREATE NORDE REDIR  ???
		ft_lstadd_back(&start, new);
		cpy = cpy->next;
	}
	if (cpy->next == NULL)
		return (NULL);
	return (start);
}

t_cmd	*ft_fill_cmd(t_token *token, t_cmd *cmd, int count_args)
{
	int	i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (i < count_args)
	{
		cmd->cmd[i] = ft_fill_string(token->content);
		i ++;
	}
	if (ft_len_juska_pipe(token) > count_args)
	{
		cmd->redir = ft_fill_redir_cmd(&token[count_args]);
		if (!cmd->redir)
			return (NULL);
	}
}

t_cmd	*ft_create_lst_cmd(t_token *token)
{
	t_token	*current;
	t_cmd	*new;
	t_cmd	*tmp;

	current = token;
	tmp = NULL;
	new = ft_init_new_cmd(ft_count_args(current));
	if (!new)
		return (error_malloc(), NULL);
	while (current)
	{
		if (current->type == PIPE && current->next != NULL)
			current = current->next;
		tmp = ft_init_new_cmd(ft_count_args(current));
		if (!tmp)
			return (error_malloc(), NULL);
		
		





	}
}

