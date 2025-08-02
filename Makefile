# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 18:42:02 by nimatura          #+#    #+#              #
#    Updated: 2025/08/02 23:05:11 by nimatura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
LDFLAGS = -lreadline -lhistory

DPS := $(SRC_FILE:.c=.d)
SRC_DIR = ./src/
SRC_FILE =	builtin_utils.c builtins.c builtins_cd.c builtins_echo.c \
			builtins_export.c builtins_unset.c collect_word.c \
			debugging_tools.c env_main.c env_utils.c error_exit.c \
			exec.c exec_utils.c execute_pipe.c expand_utils.c expansion.c \
			free_array.c free_utils.c init_shell.c main.c pars.c pars_aux.c \
			path_utils.c redirections.c retokenize.c shell_loop.c \
			signal_handling.c syntax_check.c token_tools.c tokenize.c \
			wrappers.c wrappers2.c heredoc.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILE))

OBJ_FILE := $(SRC_FILE:.c=.o)
OBJ_DIR	=	./obj/
OBJ	=	$(addprefix $(OBJ_DIR), $(OBJ_FILE))

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a
LIBFT_CHECKSUM	:=	$(LIBFT_PATH)/.last_build
LFT_FILES	:=	$(shell find $(LIBFT_PATH)/ -name '*.c' -o -name '*.h' -o \
				-name 'Makefile')
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

$(LIBFT): $(LIBFT_CHECKSUM)

$(LIBFT_CHECKSUM): $(LFT_FILES)
	@printf "%-42b%b" "$(PURPLE)Compiling libft..." "$(BLUE)$(LIBFT)$(RESET)\n"
	@make -C $(LIBFT_PATH) --silent
	@touch $@

clean:
	@printf "%b" "$(BLUE)Cleaning...$(RESET)\n"
	@if [ -d "$(LIBFT_PATH)" ]; then \
		make clean -C $(LIBFT_PATH) --silent; \
	fi
	@rm -rf $(OBJ_DIR)
	@rm -f $(LIBFT_CHECKSUM)

fclean: clean
	@printf "%b" "$(BLUE)Full cleaning...$(RESET)\n"
	@if [ -d "$(LIBFT_PATH)" ]; then \
		make fclean -C $(LIBFT_PATH) --silent; \
	fi
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
