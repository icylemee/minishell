/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_tok.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:58:19 by mlemee            #+#    #+#             */
/*   Updated: 2025/12/08 18:35:26 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "includes/libft.h"
#include "minishell.h"


t_token	*ft_lstlast_tok(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void    ft_lstadd_back_tok(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!lst)
		return ;

	// CAS 1 : La liste est vide
	if (*lst == NULL)
	{
		*lst = new;
		new->prev = NULL; // Le premier n'a personne derrière lui
		return ;
	}

	// CAS 2 : La liste contient déjà des trucs
	last = ft_lstlast_tok(*lst); // On récupère le dernier UNE SEULE FOIS
	last->next = new;        // Le dernier pointe vers le nouveau
	new->prev = last;        // Le nouveau pointe vers l'ancien dernier (Backlink)
}

// void	ft_lstadd_back_tok(t_token **lst, t_token *new)
// {
// 	if (!new)
// 		return ;
// 	if (!lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	new->prev = ft_lstlast(*lst);
// 	ft_lstlast(*lst)->next = new;
// }
