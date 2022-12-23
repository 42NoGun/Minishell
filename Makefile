# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 09:21:03 by jiyunpar          #+#    #+#              #
#    Updated: 2022/12/23 16:54:49 by jiyunpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all bonus clean fclean re

NAME			=	minishell

NAME_BONUS		=	minishell

SRCS			=	$(shell find ./src/ -iname "*.c")
OBJ_NAME		=	$(SRCS:.c=.o)

LIB_READ_LINE	=	-L${HOME}/.brew/opt/readline/lib -lreadline
LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a
INCLUDE			=	-I${HOME}/.brew/opt/readline/include -I./include
CFLAGS			=	-Wall -Wextra -Werror -Winline -UseLargePages

%.o : %.c
	@printf "\033[Kcompile 🦑 $(notdir $<)🔥\r"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all	: .all_check

minihell :
	@echo '   *     (        )  (        )       (     (     '
	@echo '(  `    )\ )  ( /(  )\ )  ( /(       )\ )  )\ )  '
	@echo ')\))(  (()/(  )\())(()/(  )\()) (   (()/( (()/(  '
	@echo '((_)()\  /(_))((_)\  /(_))((_)\  )\   /(_)) /(_))'
	@echo '(_()((_)(_))   _((_)(_))   _((_)((_) (_))  (_))  '
	@echo '|  \/  ||_ _| | \| ||_ _| | || || __|| |   | |   '
	@echo '| |\/| | | |  | .` | | |  | __ || _| | |__ | |__ '
	@echo '|_|  |_||___| |_|\_||___| |_||_||___||____||____|'
	@echo '🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥'
	@echo 'made by : jiyunpar & hanbkim & junji & cheseo'

debugs	:
	make DEBUG=2

debug	:
	make DEBUG=1

ifeq ($(DEBUG), 1)
    CFLAGS	+=	-g3
endif
ifeq ($(DEBUG), 2)
    CFLAGS	+=	-g3 -fsanitize=address
endif

.all_check	:	$(OBJ_NAME) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIB_READ_LINE) -L$(LIBFT_DIR) -lft -o $(NAME) $^
	@mkdir -p /tmp/heredoc
	@touch $@
	@make minihell

clean	:
	@rm -rf $(OBJ_NAME)
	@make -C $(LIBFT_DIR) clean

fclean	:
	@make clean
	@rm -f .all_check
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re :
	@make fclean
	@make all

$(LIBFT)	:
	@make -C $(LIBFT_DIR)
