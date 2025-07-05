NAME	=	minishell
CC		=	cc
CFLAGS	=	-g -Wall -Wextra -Werror -fsanitize=address
LDFLAGS	=	-lreadline -lhistory

OBJDIR	=	build
SRCS	=	another.c builtins.c copy_env.c error_exit.c error_msg.c excution_utils.c \
			executions.c expansion.c free_array.c free_utils.c init_shell.c main.c pars.c \
			redirections.c shell_loop.c signal_handling.c builtin_utils.c path_utils.c

OBJS	=	$(addprefix $(OBJDIR)/, ${SRCS:.c=.o})
LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

PURPLE	=	\033[0;35m
BLUE	=	\033[0;34m
RESET	=	\033[m

all: $(NAME)

$(LIBFT):
	@printf "%-42b%b" "$(PURPLE)Compiling libft..." "$(BLUE)$(@)$(RESET)\n"
	@make -C $(LIBFT_PATH) --silent
	@make bonus -C $(LIBFT_PATH) --silent

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c minishell.h | $(OBJDIR)
	@printf "%-42b%b" "$(PURPLE)Compiling $<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@printf "%-42b%b" "$(PURPLE)Linking:" "$(BLUE)$(@)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LIBFT)

clean:
	@printf "%b" "$(BLUE)Cleaning...$(RESET)\n"
	@if [ -d "$(LIBFT_PATH)" ]; then \
		make clean -C $(LIBFT_PATH) --silent; \
	fi
	@rm -rf $(OBJDIR)

fclean: clean
	@printf "%b" "$(BLUE)Full cleaning...$(RESET)\n"
	@if [ -d "$(LIBFT_PATH)" ]; then \
		make fclean -C $(LIBFT_PATH) --silent; \
	fi
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re