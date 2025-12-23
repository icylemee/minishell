/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:02:38 by mlemee            #+#    #+#             */
/*   Updated: 2025/12/02 17:32:17 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t	g_signal = 0;


/*
** Hack pour MacOS : Si la vraie readline ne marche pas,
** on crée cette fonction vide pour que le linker arrête de pleurer.
** Cela signifie juste que le CTRL-C n'effacera pas parfaitement la ligne,
** mais le shell marchera !
*/
void rl_replace_line(const char *text, int clear_undo)
{
    (void)text;
    (void)clear_undo;
}

void	handle_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
