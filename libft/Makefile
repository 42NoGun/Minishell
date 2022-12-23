# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 10:36:05 by jiyunpar          #+#    #+#              #
#    Updated: 2022/12/21 16:47:15 by jiyunpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_NAME = isalpha isdigit isalnum isascii isprint \
			toupper tolower strchr strrchr strlen strncmp \
			memset bzero memchr memcpy memcmp memmove \
			strnstr strlcpy strlcat atoi calloc strdup \
			substr strjoin strtrim split itoa strmapi terminate assert\
			striteri putchar_fd putstr_fd putendl_fd putnbr_fd \
			strcmp strjoin_left_free strjoin_right_free strjoin_no_free \
			malloc pipe write fork dup2 close chdir

SRC = $(addprefix ft_, $(addsuffix .c, $(SRC_NAME)))
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
ARFLAGS = -rcus

all : $(NAME)

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re :
	@make fclean
	@make all

$(NAME) : $(OBJ)
	@$(AR) $(ARFLAGS) $@ $?

%.o : %.c
	@printf "\033[Kcompile 🦑 $(notdir $<)🔥\r"
	@$(CC) $(CFLAGS) -I libft.h -c $< -o $@

.PHONY : all clean fclean re
