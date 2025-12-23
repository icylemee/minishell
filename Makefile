# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/09 by mlemee                  #+#    #+#              #
#    Updated: 2025/12/09 by mlemee                  ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = minishell

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -Ilibft/includes -I/opt/homebrew/opt/readline/include

# Pour trouver le .a (le code binaire)
LIBS = -L/opt/homebrew/opt/readline/lib -lreadline

# Librairies
LIBS = -lreadline

# Fichiers sources (excluant test.c)
SRCS_ROOT = \
	main.c \
	sig.c \
	utils.c \
	ft_lstadd_back_tok.c \
	ft_strcmp.c \
	ft_strdup.c \
	ft_strlcpy.c \
	ft_strlen.c

SRCS_BUILTIN = \
	built-in/ft_cd.c \
	built-in/ft_echo.c \
	built-in/ft_env.c \
	built-in/ft_exit.c \
	built-in/ft_export.c \
	built-in/ft_pwd.c \
	built-in/ft_unset.c

SRCS_ENV = \
	env/delete_env.c \
	env/init_env.c

SRCS_EXPAND = \
	expand/expand.c

SRCS_TOKENS = \
	tokens/parsing.c \
	tokens/parsing_bis.c

# Tous les fichiers sources
SRCS = $(SRCS_ROOT) $(SRCS_BUILTIN) $(SRCS_ENV) $(SRCS_EXPAND) $(SRCS_TOKENS)

# Fichiers objets
OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

# Commandes
RM = rm -rf
MKDIR = mkdir -p

# Couleurs pour les messages
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Règle par défaut
all: $(NAME)

# Création de l'exécutable
$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

# Création des fichiers objets
$(OBJS_DIR)/%.o: %.c minishell.h
	@$(MKDIR) $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS_DIR)
	@echo "$(GREEN)Clean done!$(RESET)"

# Suppression de tous les fichiers générés
fclean: clean
	@echo "$(YELLOW)Removing $(NAME)...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)Fclean done!$(RESET)"

# Recompilation complète
re: fclean all

# Règle pour vérifier que tout compile
check: all
	@echo "$(GREEN)Compilation check passed!$(RESET)"

.PHONY: all clean fclean re check
