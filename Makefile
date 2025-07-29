# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 18:42:02 by nimatura          #+#    #+#              #
#    Updated: 2025/07/29 19:44:36 by nimatura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
LDFLAGS = -lreadline -lhistory

DPS := $(SRC_FILE:.c=.d)
SRC_DIR = ./src/
SRC_FILE =	tokenize.c builtins.c env_main.c error_exit.c error_msg.c \
			exec_utils.c exec.c expansion.c free_array.c free_utils.c \
			init_shell.c main.c pars.c redirections.c retokenize.c \
			shell_loop.c signal_handling.c builtin_utils.c path_utils.c \
			expand_utils.c debugging_tools.c env_utils.c builtins_unset.c \
			builtins_export.c collect_word.c syntax_check.c wrappers2.c \
			pars_aux.c builtins_echo.c execute_pipe.c wrappers.c token_tools.c\
			builtins_cd.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILE))

OBJ_FILE := $(SRC_FILE:.c=.o)
OBJ_DIR	=	./obj/
OBJ	=	$(addprefix $(OBJ_DIR), $(OBJ_FILE))

LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a
INCLUDE = ./include/minishell.h

PURPLE	=	\033[0;35m
BLUE	=	\033[0;34m
RESET	=	\033[m

all: $(LIBFT) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEPS)
$(NAME): Makefile $(OBJ) $(LIBFT)
	@printf "%-42b%b" "$(PURPLE)Linking:" "$(BLUE)$(@)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LIBFT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE) Makefile | $(OBJ_DIR)
	@printf "%-42b%b" "$(PURPLE)Compiling $<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@printf "%-42b%b" "$(PURPLE)Compiling libft..." "$(BLUE)$(@)$(RESET)\n"
	@make -C $(LIBFT_PATH) --silent
	@make bonus -C $(LIBFT_PATH) --silent

clean:
	@printf "%b" "$(BLUE)Cleaning...$(RESET)\n"
	@if [ -d "$(LIBFT_PATH)" ]; then \
		make clean -C $(LIBFT_PATH) --silent; \
	fi
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "%b" "$(BLUE)Full cleaning...$(RESET)\n"
	@if [ -d "$(LIBFT_PATH)" ]; then \
		make fclean -C $(LIBFT_PATH) --silent; \
	fi
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
