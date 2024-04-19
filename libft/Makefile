# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 23:05:14 by muel-bak          #+#    #+#              #
#    Updated: 2024/03/12 13:43:16 by wbelfatm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

AR = ar rc

RM = rm -f

FILES = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
    ft_strlen ft_memset ft_bzero ft_memcpy \
    ft_memmove ft_strlcpy ft_strlcat \
    ft_toupper ft_tolower ft_strchr ft_strcpy ft_strcmp ft_strcat \
    ft_strrchr ft_memchr ft_memcmp ft_strnstr \
    ft_atoi ft_strncmp ft_calloc ft_strdup ft_strjoin \
    ft_substr ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_putchar_fd \
    ft_strtrim ft_strmapi ft_striteri ft_itoa ft_split ft_split_set ft_isspace ft_strstr  ft_strcmp\

FILESB = ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus \
       ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus \
       ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus    \

OBJS = $(FILES:=.o)

OBJSB = $(FILESB:=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^

bonus: $(OBJS) $(OBJSB)
	@$(AR) $(NAME) $^

%.o: %.c libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(OBJSB)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean re fclean bonus
