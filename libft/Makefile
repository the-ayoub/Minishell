# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohnudes </var/spool/mail/ohnudes>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 23:41:26 by ohnudes           #+#    #+#              #
#    Updated: 2025/07/10 20:07:49 by nimatura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del programa
NAME = libft.a

# Flags al compilar
FLAGS = -g -Wall -Wextra -Werror

# DIRs
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/

# Sources files
SRC_FILE = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		   ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strlcat.c \
		   ft_strlcpy.c ft_strlen.c ft_tolower.c ft_toupper.c ft_strchr.c \
		   ft_strrchr.c ft_strncmp.c ft_memcmp.c ft_memchr.c ft_strnstr.c \
		   ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		   ft_strtrim.c ft_split.c ft_itoa.c ft_striteri.c ft_strmapi.c \
		   ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_putnbr_fd.c \
		   ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		   ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		   ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
		   ft_printf.c ft_printf_tools.c ft_printf_convert.c get_next_line.c \
		   get_next_line_utils.c ft_isspace.c ft_strcmp.c

OBJ_FILE = $(SRC_FILE:.c=.o)
INC_FILE = libft.h ft_printf.h get_next_line.h

# Elements
SRC	= $(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_FILE))
INCS = $(addprefix $(INC_DIR), $(INC_FILE))

# Flags for linking
LNK = ar rc

#### Compilacion del programa ####

all: $(NAME)

$(NAME): $(OBJ) 
	@echo Creating library $(NAME)...
	@$(LNK) $@ $^ 
	@echo $(NAME) completed.

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR) Makefile
	@gcc $(FLAGS) -I$(INC_DIR) -o $@ -c $<

$(OBJ_DIR):
	mkdir obj

fclean: clean
	@rm -f $(NAME) 

clean:
	@rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
