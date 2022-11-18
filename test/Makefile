# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 09:21:03 by jiyunpar          #+#    #+#              #
#    Updated: 2022/11/18 10:09:06 by jiyunpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all bonus clean fclean re

NAME = test

SRCS	:= $(shell find ../src -iname "*.c" | grep -v "main.c")
SRCS	+= $(shell find . -iname "*.c")
OBJS	:= $(SRCS:.c=.o)

OBJ_DIR = test_obj

READ_LINE_DIR = -L/opt/homebrew/opt/readline/lib
READ_LINE_LIB = -lreadline

LIBFT_DIR = ../libft/
LIBFT_LIB = libft.a

INCLUDE = -I/opt/homebrew/opt/readline/include -I../include/

CFLAGS = -Wall -Wextra -Werror

all : all_check

debugs : 
	make DEBUG=2

debug :
	make DEBUG=1

ifeq ($(DEBUG), 1)
    CFLAGS	+=	-g3 #-save-temps=obj
endif
ifeq ($(DEBUG), 2)
    CFLAGS	+=	-g3 -fsanitize=address # -save-temps=obj
endif

all_check : $(OBJS) $(LIBFT_LIB)
		$(CC) $(CFLAGS) $(INCLUDE) $(READ_LINE_DIR) $(READ_LINE_LIB) -L$(LIBFT_DIR) -lft -o $(NAME) $^
		touch $@

clean :
		rm -rf $(OBJS)
		rm -rf *.s
		rm -rf *.i
		rm -rf *.bc

fclean : clean
		rm -f $(NAME)
		rm -f all_check

re :
		make fclean
		make all

$(LIBFT_LIB) : 
		make -C $(LIBFT_DIR)
		cp $(LIBFT_DIR)$(LIBFT_LIB) .

%.o : %.c
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
