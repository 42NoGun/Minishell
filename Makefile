# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 09:21:03 by jiyunpar          #+#    #+#              #
#    Updated: 2022/12/07 11:45:39 by jiyunpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all bonus clean fclean re

NAME = minishell

NAME_BONUS = minishell

SRCS	:= $(shell find ./src/ -iname "*.c")
# SRCS	+= $(shell find ./src/data_structure -iname "*.c")
# SRCS	+= $(shell find ./src/execution -iname "*.c")
# SRCS	+= $(shell find ./src/expansion -iname "*.c")
# SRCS	+= $(shell find ./src/parser -iname "*.c")
# SRCS	+= $(shell find ./src/tokenizer -iname "*.c")
# SRCS	+= $(shell find ./src/utils -iname "*.c")
# SRCS	+= $(shell find ./src/execution -iname "*.c")
# SRCS	+= $(shell find ./src/execution -iname "*.c")

# linked_list_function_1.c linked_list_function_2.c

# SRC_BONUS_DIR = ./src_bonus/
# SRC_BONUS_NAME = main_bonus.c check_file.c read_map.c get_coordinate.c \
# 			init_struct.c rotate.c fdf_bonus.c draw_line.c \
# 			get_next_line.c get_next_line_utils.c \
# 			key_hook_1_bonus.c key_hook_2_bonus.c put_string_bonus.c\
# 			fdf_utils_1.c fdf_utils_2.c \
# 			linked_list_function_1.c linked_list_function_2.c
# SRC_BONUS = $(addprefix $(SRC_BONUS_DIR),$(SRC_BONUS_NAME))

# OBJ_DIR = ./obj/
OBJ_NAME = $(SRCS:.c=.o)
# OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

# LIB_READ_LINE = -L/opt/homebrew/opt/readline/lib -lreadline
LIB_READ_LINE = -L${HOME}/.brew/opt/readline/lib -lreadline
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# OBJ_BONUS_DIR = ./obj_bonus/
# OBJ_BONUS_NAME = $(SRC_BONUS_NAME:.c=.o)
# OBJ_BONUS = $(addprefix $(OBJ_BONUS_DIR),$(OBJ_BONUS_NAME))

INCLUDE = -I${HOME}/.brew/opt/readline/include -I./include


# gcc -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include src/main.c

CFLAGS = -g3 -fsanitize=address

all : all_check

debugs : 
	make DEBUG=2

debug :
	make DEBUG=1

# ifeq ($(DEBUG), 1)
#     CFLAGS	+=	-g3 #-save-temps=obj
# endif
# ifeq ($(DEBUG), 2)
#     CFLAGS	+=	-g3 -fsanitize=address #-save-temps=obj
#endif

all_check : $(OBJ_NAME) $(LIBFT)
		$(CC) $(CFLAGS) $(INCLUDE) $(LIB_READ_LINE) -L$(LIBFT_DIR) -lft -o $(NAME) $^
		touch $@
		
clean :
		rm -rf $(OBJ_NAME)

fclean : clean
		rm -f $(NAME)
		rm -f all_check
		rm -rf ../**.s
		rm -rf ../**.i
		rm -rf ../**.bc

re :
		make fclean
		make all

$(LIBFT) : 
		make -C $(LIBFT_DIR)
# @mkdir -p $(OBJ_DIR)
# $(OBJ_DIR)%.o : $(SRC_DIR)%.c
# 		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.o : %.c
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
