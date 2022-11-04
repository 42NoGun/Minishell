# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 09:21:03 by jiyunpar          #+#    #+#              #
#    Updated: 2022/11/04 14:51:00 by jiyunpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all bonus clean fclean re

NAME = minishell

NAME_BONUS = minishell

SRC_DIR = ./src/
SRC_NAME = main.c 
# linked_list_function_1.c linked_list_function_2.c
SRC = $(addprefix $(SRC_DIR),$(SRC_NAME))

# SRC_BONUS_DIR = ./src_bonus/
# SRC_BONUS_NAME = main_bonus.c check_file.c read_map.c get_coordinate.c \
# 			init_struct.c rotate.c fdf_bonus.c draw_line.c \
# 			get_next_line.c get_next_line_utils.c \
# 			key_hook_1_bonus.c key_hook_2_bonus.c put_string_bonus.c\
# 			fdf_utils_1.c fdf_utils_2.c \
# 			linked_list_function_1.c linked_list_function_2.c
# SRC_BONUS = $(addprefix $(SRC_BONUS_DIR),$(SRC_BONUS_NAME))

OBJ_DIR = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

READ_LINE_DIR = -L/opt/homebrew/opt/readline/lib
READ_LINE_LIB = -lreadline

# OBJ_BONUS_DIR = ./obj_bonus/
# OBJ_BONUS_NAME = $(SRC_BONUS_NAME:.c=.o)
# OBJ_BONUS = $(addprefix $(OBJ_BONUS_DIR),$(OBJ_BONUS_NAME))

INCLUDE = -I/opt/homebrew/opt/readline/include


# gcc -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include src/main.c

CFLAGS = -Wall -Wextra -Werror

all : all_check

debugs : 
	make DEBUG=2

debug :
	make DEBUG=1

ifeq ($(DEBUG), 1)
    CFLAGS	+=	-g3 -save-temps=obj
endif
ifeq ($(DEBUG), 2)
    CFLAGS	+=	-g3 -fsanitize=address -save-temps=obj
endif

all_check : $(OBJ)
		$(CC) $(CFLAGS) $(INCLUDE) $(READ_LINE_DIR) $(READ_LINE_LIB) -o $(NAME) $^
		touch $@
		
bonus : bonus_check

bonus_check : $(OBJ_BONUS) $(MLX_LIB)
		$(CC) $(CFLAGS) $(INCLUDE) -framework OpenGL -framework AppKit -o $(NAME_BONUS) $^
		touch $@
		
clean :
		rm -rf $(OBJ_DIR)
		rm -rf $(OBJ_BONUS_DIR)

fclean : clean
		rm -f $(NAME)
		rm -f all_check
		rm -f bonus_check

re :
		make fclean
		make all

$(MLX_LIB) : 
		make -C $(MLX_LIB_DIR)
		cp $(MLX_LIB_DIR)$(MLX_LIB) .

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_BONUS_DIR)%.o : $(SRC_BONUS_DIR)%.c
		mkdir -p $(OBJ_BONUS_DIR)
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
