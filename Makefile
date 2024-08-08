# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 15:49:51 by ltrevin-          #+#    #+#              #
#    Updated: 2024/08/08 15:40:10 by ltrevin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## COLORS
RESET   		= \033[0m
BLACK   		= \033[0;30m
RED     		= \033[0;31m
GREEN   		= \033[0;32m
YELLOW  		= \033[0;33m
BLUE    		= \033[0;34m
MAGENTA 		= \033[0;35m
CYAN   			= \033[0;36m
WHITE   		= \033[0;37m

BOLD    		= \033[1m
UNDERLINE 		= \033[4m

########## VARS CONFIG ##########

CC              = gcc
CFLAGS          = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS         = -L./include/libft -lft
RM              = rm -f
MKDIR_P         = mkdir -p
NAME            = minitalk
DEPS			=  Makefile include/minitalk.h 
# Executables
NAME_SERVER     = server
NAME_CLIENT     = client

NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

########## PATHS ##########

INCLUDE_PATH    = ./include
SRC_DIR         = ./src
OBJ_DIR         = ./obj

########## SOURCE FILES ##########

# Source Files
SRC_SERVER      = $(SRC_DIR)/server.c
SRC_CLIENT      = $(SRC_DIR)/client.c

SRC_SERVER_BONUS = $(SRC_DIR)/server_bonus.c
SRC_CLIENT_BONUS = $(SRC_DIR)/client_bonus.c

# Object Files
OBJ_SERVER      = $(SRC_SERVER:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT      = $(SRC_CLIENT:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

########## RULES ##########

all: libft $(NAME_SERVER) $(NAME_CLIENT)

bonus: libft $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER): $(OBJ_SERVER)
	@$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER) $(LDFLAGS)
	@echo "$(BOLD)$(BLUE)󰒋 $(CYAN)$(NAME_SERVER) $(YELLOW)is ready to work!$(RESET)"

$(NAME_CLIENT): $(OBJ_CLIENT)
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT) $(LDFLAGS)
	@echo "$(BOLD)$(BLUE)󰓃 $(CYAN)$(NAME_CLIENT) $(YELLOW)is ready to work!$(RESET)"

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) -o $(NAME_SERVER_BONUS) $(LDFLAGS)
	@echo "$(BOLD)$(BLUE)󰒋 $(CYAN)$(NAME_SERVER_BONUS) $(YELLOW) is ready to work!$(RESET)"

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) -o $(NAME_CLIENT_BONUS) $(LDFLAGS)
	@echo "$(BOLD)$(BLUE)󰓃 $(CYAN)$(NAME_CLIENT_BONUS) $(YELLOW)is ready to work!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS) | $(OBJ_DIR)
	@$(MKDIR_P) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE_PATH)
	@echo "$(GREEN)🛠 $(MAGENTA)$(@F:.o=) $(BLUE)object created!$(RESET)"

$(OBJ_DIR):
	@$(MKDIR_P) $(OBJ_DIR)

libft:
	@$(MAKE) -C include/libft bonus --no-print-directory

########## CLEANING ##########

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "🧼 Removed object files from minitalk"

fclean: clean
	@$(MAKE) -C include/libft fclean --no-print-directory
	@$(RM) -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
	@echo "🛁 Removed executables"

re: fclean all

.PHONY: all clean fclean re bonus libft

