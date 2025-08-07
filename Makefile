# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 15:02:26 by akolupae          #+#    #+#              #
#    Updated: 2025/08/07 17:10:17 by akolupae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_C = client
NAME_S = server

CC = cc
CFLAGS = -Wall -Werror -Wextra

HDR = minitalk.h

SRC_C = client.c

SRC_S = server.c

SRC_COMMON = utils.c

OBJ_DIR = obj
OBJ_C = $(SRC_C:%.c=$(OBJ_DIR)/%.o)
OBJ_S = $(SRC_S:%.c=$(OBJ_DIR)/%.o)
OBJ_COMMON = $(SRC_COMMON:%.c=$(OBJ_DIR)/%.o)

LIB_DIR = libft
LIB_NAME = $(LIB_DIR)/libft.a
LIB_HDR = $(LIB_DIR)/libft.h

COLOR = \033[1;32m
RESET = \033[0m

all: $(NAME_C) $(NAME_S)

$(NAME_C): $(OBJ_C) $(OBJ_COMMON) $(LIB_NAME)
	@echo "$(COLOR) Building $@$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(OBJ_C) $(OBJ_COMMON) $(LIB_NAME)

$(NAME_S): $(OBJ_S) $(OBJ_COMMON) $(LIB_NAME)
	@echo "$(COLOR) Building $@$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(OBJ_S) $(OBJ_COMMON) $(LIB_NAME)

$(OBJ_DIR)/%.o: %.c $(HDR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LIB_NAME): $(LIB_HDR)
	@$(MAKE) -C $(LIB_DIR)

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@echo "$(COLOR) Cleaning $(NAME_C) and $(NAME_S)$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(COLOR) Removing $(LIB_NAME)$(RESET)"
	@rm -f $(LIB_NAME)
	@echo "$(COLOR) Removing $(NAME_C) and $(NAME_S)$(RESET)"
	@rm -f $(NAME_C) $(NAME_S)

re: fclean all

.SECONDARY: $(OBJ_DIR) $(OBJ_C) $(OBJ_S) $(OBJ_COMMON)
.PHONY: all clean fclean re
