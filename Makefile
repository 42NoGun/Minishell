# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 09:21:03 by jiyunpar          #+#    #+#              #
#    Updated: 2023/01/18 16:09:43 by cheseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all bonus clean fclean re

NAME				:=	minishell

BUILT_IN			:=	cd echo env exit export_utils export pwd unset do_builtin
BUILT_IN_M			:=	$(addprefix src/built_in/, $(addsuffix .c, $(BUILT_IN)))
BUILT_IN_B			:=	$(addprefix src_bonus/built_in/, $(addsuffix _bonus.c, $(BUILT_IN)))

DATA_STRUCTURE		=	binary_tree_function_1 binary_tree_function_2 \
					linked_list_function_1 linked_list_function_2
DATA_STRUCTURE_M	:=	$(addprefix src/data_structure/, $(addsuffix .c, $(DATA_STRUCTURE)))
DATA_STRUCTURE_B	:=	$(addprefix src_bonus/data_structure/, $(addsuffix _bonus.c, $(DATA_STRUCTURE)))

EXECUTION			:=	child child_utils convert_tree_to_exec_list execute pipe redirect refine_and_get_field_index refine_field
EXECUTION_M			:=	$(addprefix src/execution/, $(addsuffix .c, $(EXECUTION)))
EXECUTION_B			:=	$(addprefix src_bonus/execution/, $(addsuffix _bonus.c, $(EXECUTION)))

EXPANSION			:=	concat_content expand expand_dollar expand_wildcard
EXPANSION_M			:=	$(addprefix src/expansion/, $(addsuffix .c, $(EXPANSION)))
EXPANSION_B			:=	$(addprefix src_bonus/expansion/, $(addsuffix _bonus.c, $(EXPANSION)))

HEREDOC				:=	heredoc heredoc_utils heredoc_utils1
HEREDOC_M			:=	$(addprefix src/heredoc/, $(addsuffix .c, $(HEREDOC)))
HEREDOC_B			:=	$(addprefix src_bonus/heredoc/, $(addsuffix _bonus.c, $(HEREDOC)))

PARSER				:=	check_pair check_syntax parser put_token read_content tokenize tokenize_is_utils tokenize_utils
PARSER_M			:=	$(addprefix src/parser/, $(addsuffix .c, $(PARSER)))
PARSER_B			:=	$(addprefix src_bonus/parser/, $(addsuffix _bonus.c, $(PARSER)))

SIGNAL				:=	signal
SIGNAL_M			:=	$(addprefix src/signal/, $(addsuffix .c, $(SIGNAL)))
SIGNAL_B			:=	$(addprefix src_bonus/signal/, $(addsuffix _bonus.c, $(SIGNAL)))

SUBSHELL			:=	subshell
SUBSHELL_M			:=	$(addprefix src/subshell/, $(addsuffix .c, $(SUBSHELL)))
SUBSHELL_B			:=	$(addprefix src_bonus/subshell/, $(addsuffix _bonus.c, $(SUBSHELL)))

UTILS				:=	execute_utils free1 free2 main_utils main_utils1 utils utils1 utils2
UTILS_M				:=	$(addprefix src/utils/, $(addsuffix .c, $(UTILS)))
UTILS_B				:=	$(addprefix src_bonus/utils/, $(addsuffix _bonus.c, $(UTILS)))

MAIN				:= 	main
MAIN_M				:=	$(addprefix src/, $(addsuffix .c, $(MAIN)))
MAIN_B				:=	$(addprefix src_bonus/, $(addsuffix _bonus.c, $(MAIN)))

SRCS				:=	$(BUILT_IN_M) $(DATA_STRUCTURE_M) $(EXECUTION_M) $(EXPANSION_M) \
						$(HEREDOC_M) $(PARSER_M) $(SIGNAL_M) $(SUBSHELL_M) $(UTILS_M) $(MAIN_M)

SRCS_B				:=	$(BUILT_IN_B) $(DATA_STRUCTURE_B) $(EXECUTION_B) $(EXPANSION_B) \
						$(HEREDOC_B) $(PARSER_B) $(SIGNAL_B) $(SUBSHELL_B) $(UTILS_B) $(MAIN_B)

OBJS				:=	$(SRCS:.c=.o)
B_OBJS				:=	$(SRCS_B:.c=.o)

LIB_READ_LINE		=	-L$(shell brew --prefix readline)/lib -lreadline
LIBFT_DIR			=	./libft
LIBFT				=	$(LIBFT_DIR)/libft.a
INCLUDE				=	-I$(shell brew --prefix readline)/include -I./include
CFLAGS				=	-Wall -Wextra -Werror -Winline -UseLargePages

%.o : %.c
	@printf "\033[Kcompile 🦑 $(notdir $<)🔥\r"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all	: .all_check

bonus : .all_check

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

.all_check	:	$(if $(filter bonus, $(MAKECMDGOALS)), $(B_OBJS), $(OBJS))
	@make -C $(LIBFT_DIR) re
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIB_READ_LINE) -L$(LIBFT_DIR) -lft -o $(NAME) $^
	@mkdir -p /tmp/heredoc
	@touch $@
	@make minihell

clean	:
	@rm -rf $(OBJS)
	@rm -rf $(B_OBJS)
	@make -C $(LIBFT_DIR) clean

fclean	:
	@make clean
	@rm -f .all_check
	@rm -f $(NAME)
	@rm -rf /tmp/heredoc
	@make -C $(LIBFT_DIR) fclean

re :
	@make fclean
	@make all
