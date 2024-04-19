# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 13:23:26 by wbelfatm          #+#    #+#              #
#    Updated: 2024/04/15 04:22:44 by muel-bak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -I/Users/$(USER)/homebrew/Cellar/readline/8.2.7/include
CC = cc
RM = rm -f
USER = muel-bak

SRC = main.c ./parsing/trees.c ./utils/utils.c ./parsing/parse.c ./execution/execute.c ./execution/here_doc.c ./expanding/expand.c \
	  ./lexing/lexer.c ./memory/memory.c ./utils/append.c ./utils/extract.c ./utils/remove.c ./utils/insert.c \
	  builtins/ft_cd.c builtins/ft_cd_utils.c builtins/ft_cd_utils1.c \
	  builtins/ft_echo.c builtins/ft_env.c builtins/ft_export.c builtins/ft_export_utils.c \
	  builtins/ft_pwd.c builtins/ft_unset.c builtins/env_utils.c \
	  builtins/env_utils2.c builtins/env_utils3.c ./utils/signals.c syntax/ft_strtok.c \
	  syntax/ft_syntax.c syntax/ft_syntax1.c syntax/ft_syn_token.c \
	  ./execution/execute_redir.c ./execution/execute_condition.c ./execution/execute_pipe.c ./execution/execute_builtin.c \
	  ./utils/redir_utils.c ./execution/execute_subshell.c ./execution/execute_single.c ./execution/execute_utils.c \
	  ./expanding/match.c ./expanding/expand_utils.c ./expanding/expand_special.c ./expanding/expand_dollar.c ./expanding/expand_star.c \
	  ./utils/extract_utils.c ./lexing/eval.c ./lexing/eval_utils.c ./utils/eval_content.c ./utils/content_list.c \
	  ./expanding/match_utils.c ./parsing/parse_rest.c ./parsing/tree_utils.c ./memory/memory_utils.c \
	  ./utils/ft_is_something.c ./utils/global_utils.c ./utils/main_utils.c ./utils/main_utils_1.c ./utils/main_utils_2.c \

LIBFT_FILES = ./libft/ft_isalpha.c ./libft/ft_isdigit.c ./libft/ft_isalnum.c ./libft/ft_isascii.c ./libft/ft_isprint.c \
    ./libft/ft_strlen.c ./libft/ft_memset.c ./libft/ft_bzero.c ./libft/ft_memcpy.c \
    ./libft/ft_memmove.c ./libft/ft_strlcpy.c ./libft/ft_strlcat.c \
    ./libft/ft_toupper.c ./libft/ft_tolower.c ./libft/ft_strchr.c ./libft/ft_strcpy.c ./libft/ft_strcmp.c ./libft/ft_strcat.c \
    ./libft/ft_strrchr.c ./libft/ft_memchr.c ./libft/ft_memcmp.c ./libft/ft_strnstr.c \
    ./libft/ft_atoi.c ./libft/ft_strncmp.c ./libft/ft_calloc.c ./libft/ft_strdup.c ./libft/ft_strjoin.c \
    ./libft/ft_substr.c ./libft/ft_putstr_fd.c ./libft/ft_putendl_fd.c ./libft/ft_putnbr_fd.c ./libft/ft_putchar_fd.c \
    ./libft/ft_strtrim.c ./libft/ft_strmapi.c ./libft/ft_striteri.c ./libft/ft_itoa.c ./libft/ft_split.c ./libft/ft_split_set.c\
	./libft/ft_isspace.c ./libft/ft_strstr.c  ./libft/ft_strcmp.c ./libft/libft.h\

OBJS = ${SRC:.c=.o}

NAME = minishell
LIBFT = ./libft/libft.a

all: $(NAME)

$(LIBFT): $(LIBFT_FILES)
	@make -C ./libft/

%.o: %.c minishell.h
	@$(CC) -c $(CFLAGS)  $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -lreadline -L/Users/$(USER)/homebrew/Cellar/readline/8.2.7/lib -o $(NAME)

clean:
	@make clean -C ./libft/ && $(RM) $(OBJS)

fclean: clean
	@make fclean -C ./libft/ && $(RM) $(NAME)
	
re: fclean $(NAME)

.PHONY: clean fclean all re bonus