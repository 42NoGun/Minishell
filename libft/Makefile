# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunpar <jiyunpar@student.42seou.kr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 10:36:05 by jiyunpar          #+#    #+#              #
#    Updated: 2022/07/20 13:22:46 by jiyunpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_NAME_MAN = isalpha isdigit isalnum isascii isprint \
			toupper tolower strchr strrchr strlen strncmp \
			memset bzero memchr memcpy memcmp memmove \
			strnstr strlcpy strlcat atoi calloc strdup \
			substr strjoin strtrim split itoa strmapi \
			striteri putchar_fd putstr_fd putendl_fd putnbr_fd \
			
SRC_NAME_BONUS = lstnew lstadd_front lstsize lstlast lstadd_back lstdelone \
					lstclear lstiter lstmap
 
SRC_MAN = $(addprefix ft_, $(addsuffix .c, $(SRC_NAME_MAN)))
SRC_BONUS = $(addprefix ft_, $(addsuffix .c, $(SRC_NAME_BONUS)))
OBJ_MAN = $(SRC_MAN:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ = $(OBJ_MAN) $(OBJ_BONUS)
else
	OBJ = $(OBJ_MAN)
endif

CFLAGS= -Wall -Wextra -Werror
ARFLAGS = -rcus

all : $(NAME)

bonus :
	@make WITH_BONUS=1 all

clean :
		rm -f $(OBJ_MAN) $(OBJ_BONUS)

fclean : clean
		rm -f $(NAME)

re :
	make fclean
	make all

$(NAME) : $(OBJ)
		$(AR) $(ARFLAGS) $@ $?

%.o : %.c
		$(CC) $(CFLAGS) -I libft.h -c $< -o $@

.PHONY : all clean fclean re
