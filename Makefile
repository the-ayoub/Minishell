# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: farges <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 02:38:26 by farges            #+#    #+#              #
#    Updated: 2025/04/26 02:51:11 by farges           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
AR		=	ar
ARFLAGS	=	-rcs
CC		=	cc
CFLAGS	=	-g -Wall -Wextra -Werror 

OBJDIR	=	build
SRCS	=	main.c	
OBJS	=	$(addprefix $(OBJDIR)/, ${SRCS:.c=.o})
LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

PURPLE	=	\033[0;35m
BLUE	=	\033[0;34m
RESET	=	\033[m

all: $(NAME)

$(LIBFT):
	@printf "%-42b%b" "$(PURPLE)$(*F):" "$(BLUE)$(@)$(RESET)\n"
	@make -C $(LIBFT_PATH) --silent

$(OBJS): $(OBJDIR)/%.o : %.c minishell.h | $(OBJDIR)
	@printf "%-42b%b" "$(PURPLE)$(<):" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir $(OBJDIR)

$(NAME): $(OBJS) $(LIBFT)
	@printf "%-42b%b" "$(PURPLE)$(*F)minishell:" "$(BLUE)$(@)$(RESET)\n"
	@cp $(LIBFT) $@
	@$(CC) $(CFLAGS) $^ -o $(NAME)

fclean: clean
	@printf "%b" "$(BLUE)$(@)ing...$(RESET)\n"
	@make $@ -C $(LIBFT_PATH) --silent
	@rm -rf $(NAME)

clean:
	@printf "%b" "$(BLUE)$(@)ing...$(RESET)\n"
	@make $@ -C $(LIBFT_PATH) --silent
	@rm -rf $(OBJDIR)

re:    fclean all

.PHONY: all clean fclean re $(LIBFT)

