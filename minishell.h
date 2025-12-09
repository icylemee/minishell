/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:35:04 by mlemee            #+#    #+#             */
/*   Updated: 2025/12/08 22:49:09 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Librairies communes
# include "libft/includes/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// Librairies parsing
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>

// Libraries  exec
# include <errno.h>
# include <limits.h>
# include <sys/types.h>

# define SING_QUOTE_D 39
# define DOUB_QUOTE_D 34



typedef struct s_env	t_env2;
extern volatile sig_atomic_t	g_signal;

typedef struct s_env
{
	char *key_env; // on va stock jusqu'au premier '=',ex "USER=" mais on stock ce quil y a avant donc jsute "USER"
	char *value_env;      // on stock ce quil y a apres la key de la ligne d'env

	t_env2 *next; // vers la prochaine string de **env
}						t_env2;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN, //<
	REDIR_OUT, //>
	REDIR_D_OUT, //>>
	HEREDOC, //<<
	ARG_REDIR // arguemnt de la redir
}			t_token_type;

typedef enum e_quote_state
{
	NO_QUOTE_T,
	SINGLE_QUOTE_T,
	DOUBLE_QUOTE_T
}			t_quote_state;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	t_quote_state	state;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;


//GESTION CREATION LISTE ENVIRONNEMENT 
t_env2	*ft_create_list_env(char **env);
t_env2	*ft_init_node_env(char *env);
char	*ft_extract_value_env(char *str);
int		ft_strlen_value_env(int index_egal, char *str);
char	*ft_extract_key_env(char *str);
int		ft_strlen_key_env(char *str);
void	ft_lstclear(t_env2 **lst, void (*del)(void*));
void	ft_lstdelone(t_env2 *lst, void (*del)(void *));
void	del_node_env(void *node);

// GESTION SIGNAUX
void	handle_sigint(int sig);


// GESTION TOKEN
t_token	*ft_create_list_tokens(char *line);
int		ft_check_quote(char c);
char	*ft_fill_word_which_q(char *line, char *word, int quote);
char	*ft_fill_word_quote(char *line);
char	*ft_fill_word(char *line);
int		ft_check_redir_n_pipe(char *line);
char	*ft_fill_word_pipe_n_redir(char *line, t_token_type type);
t_token	*ft_create_token(char *word, t_token_type type, t_quote_state state);
t_quote_state	ft_quote_state(char c);
t_token	*ft_lstlast_tok(t_token *lst);
void	ft_lstadd_back_tok(t_token **lst, t_token *new);
void	ft_lstclear_token(t_token **lst);

// GESTION EXPAND 
char	*ft_getenv(char *key, t_env2 *env);








size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_append_token(t_token **start, char *word,
			t_token_type type, t_quote_state state);
char	*ft_strdup(const char *s);

static char	*ft_strcpy(char *dest, const char *src);

void	error_malloc(void);
void	ft_putendl_fd(char *s, int fd);



#endif
