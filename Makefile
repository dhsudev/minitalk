########## VARS CONFIG ##########

CC              = gcc
CFLAGS          = -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS         = -L./include/libft -lft
RM              = rm -f
MKDIR_P         = mkdir -p
NAME            = minitalk

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

# Default rule
all: $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER): $(OBJ_SERVER) | libft
	@$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER) $(LDFLAGS)
	@echo "󰒋 $(NAME_SERVER) is ready to work!"

$(NAME_CLIENT): $(OBJ_CLIENT) | libft
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT) $(LDFLAGS)
	@echo "󰓃 $(NAME_CLIENT) is ready to work!"

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS) | libft
	@$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) -o $(NAME_SERVER_BONUS) $(LDFLAGS)
	@echo "󰒋 $(NAME_SERVER_BONUS) is ready to work!"

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS) | libft
	@$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) -o $(NAME_CLIENT_BONUS) $(LDFLAGS)
	@echo "󰓃 $(NAME_CLIENT_BONUS) is ready to work!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(MKDIR_P) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE_PATH)
	@echo "🛠  $(@F:.o=) object created!"

$(OBJ_DIR):
	@$(MKDIR_P) $(OBJ_DIR)

libft:
	@$(MAKE) -C include/libft bonus --no-print-directory

########## CLEANING ##########

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "🧼 Removed object files"

fclean: clean
	@$(MAKE) -C include/libft fclean --no-print-directory
	@$(RM) -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
	@echo "🛁 Removed executables"

re: fclean all

.PHONY: all clean fclean re bonus libft

