# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 15:02:26 by akolupae          #+#    #+#              #
#    Updated: 2025/07/15 18:32:04 by akolupae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1 = client
NAME_2 = server

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

HDR = minitalk.h
HDR_B = minitalk_bonus.h

SRC = \
	client.c \
	server.c \

SRC_B = \
	client_bonus.c \
	server_bonus.c \

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_B = $(SRC_B:%.c=$(OBJ_DIR)/%.o)

LIB_DIR = libft
LIB_NAME = $(LIB_DIR)/libft.a
LIB_HDR = $(LIB_DIR)/libft.h

COLOR = \033[1;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIB_NAME)
	@echo "$(COLOR) Building $@$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJ_DIR) $(OBJ_B) $(LIB_NAME)
	@echo "$(COLOR) Building $@$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME_B) $(OBJ_B) $(LIB_NAME)

$(LIB_NAME): $(LIB_HDR)
	@$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HDR) $(HDR_B)
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@echo "$(COLOR) Cleaning $(NAME) and $(NAME_B)$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(COLOR) Removing $(LIB_NAME)$(RESET)"
	@rm -f $(LIB_NAME)
	@echo "$(COLOR) Removing $(NAME) and $(NAME_B)$(RESET)"
	@rm -f $(NAME) $(NAME_B)

re: fclean all

.SECONDARY: $(OBJ_DIR) $(OBJ) $(OBJ_B)
.PHONY: all clean fclean re bonus
