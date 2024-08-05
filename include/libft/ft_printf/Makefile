# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 16:20:31 by ltrevin-          #+#    #+#              #
#    Updated: 2024/08/01 16:15:23 by ltrevin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


##########  VARS CONFIG
NAME            = libftprintf.a
HEADER_FILE     = ft_printf.h
CC              = gcc
FLAGS           = -Wall -Wextra -Werror
AR              = ar rcs

##########  PATHS
SRCS_PATH       = ./src
INCLUDE_PATH    = ./include
OBJ_DIR         = ./obj

##########  VARS FILES
SRC_FILES       = ft_printf.c ft_numbers.c
OBJECTS         = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

##########  RULES
all: $(NAME)

$(NAME): $(INCLUDE_PATH)/$(HEADER_FILE) $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)
	@echo "🔅 Printf is ready to work!"

$(OBJ_DIR)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDE_PATH)
	@echo "🛠  $(@F) object created!"

.PHONY: all clean fclean re

clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧼 Removed object files from printf!"

fclean: clean
	@rm -f $(NAME)
	@echo "🛁 Removed $(NAME) file!"

re: fclean all
