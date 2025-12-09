
#include "minishell.h"


void debug_print_tokens(t_token *tokens)
{
    if (!tokens)
        return ;
    printf("\n--- VISUALISATION DES TOKENS ---\n");
    while (tokens)
    {
        printf("[TOKEN] Content: '%s' | Type: %d | Quote: %d\n", 
               tokens->content, tokens->type, tokens->state);
        tokens = tokens->next;
    }
    printf("--------------------------------\n\n");
}

void ft_lstclear_token(t_token **lst)
{
    t_token *current;
    t_token *next_node;

    // Sécurité : si la liste n'existe pas, on ne fait rien
    if (!lst)
        return ;
    
    current = *lst;
    while (current)
    {
        // 1. IMPORTANT : On sauvegarde l'adresse du suivant AVANT de détruire l'actuel
        next_node = current->next;

        // 2. On libère la string à l'intérieur (le content)
        if (current->content)
            free(current->content);

        // 3. On libère le maillon lui-même (la structure)
        free(current);

        // 4. On passe au suivant qu'on avait sauvegardé
        current = next_node;
    }
    
    // Bonne pratique : on met le pointeur de départ à NULL pour éviter les "dangling pointers"
    *lst = NULL;
}

int main(int ac, char **av)
{
    if (ac > 1)
    {
        t_token *list = ft_create_list_tokens(av[1]);
        t_token *current = list;
        debug_print_tokens(list);
        ft_lstclear_token(&list);
    }
    return (0);
}