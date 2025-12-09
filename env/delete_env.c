/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:53:49 by mlemee            #+#    #+#             */
/*   Updated: 2025/12/08 21:54:16 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_env2 **lst, void (*del)(void*))
{
	t_env2	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_lstdelone(t_env2 *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (lst->key_env)
		del(lst->key_env);
	if (lst->value_env)
		del(lst->value_env);
	free(lst);
}

void	del_node_env(void *node)
{
	free(node);
}