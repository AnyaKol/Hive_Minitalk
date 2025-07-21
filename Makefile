# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 15:02:26 by akolupae          #+#    #+#              #
#    Updated: 2025/07/21 13:21:16 by akolupae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_C = client
NAME_S = server

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

HDR = minitalk.h
#HDR_B = minitalk_bonus.h

SRC_C = \
	client.c \

SRC_S = \
	server.c \	

#SRC_CB = \
#	client_bonus.c \

#SRC_SB = \
#	server_bonus.c \

OBJ_DIR = obj
OBJ_C = $(SRC_C:%.c=$(OBJ_DIR)/%.o)
OBJ_S = $(SRC_S:%.c=$(OBJ_DIR)/%.o)
#OBJ_CB = $(SRC_CB:%.c=$(OBJ_DIR)/%.o)
#OBJ_SB = $(SRC_SB:%.c=$(OBJ_DIR)/%.o)

LIB_DIR = libft
LIB_NAME = $(LIB_DIR)/libft.a
LIB_HDR = $(LIB_DIR)/libft.h

COLOR = \033[1;32m
RESET = \033[0m

all: $(NAME_C) $(NAME_S)

$(NAME_C): $(OBJ_DIR) $(OBJ_C) $(LIB_NAME)
	@echo "$(COLOR) Building $@$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_C) $(LIB_NAME)

$(NAME_S): $(OBJ_DIR) $(OBJ_S) $(LIB_NAME)
	@echo "$(COLOR) Building $@$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_S) $(LIB_NAME)

#bonus: $(NAME_C) $(NAME_S)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HDR)
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

.SECONDARY: $(OBJ_DIR) $(OBJ_C) $(OBJ_S)
.PHONY: all clean fclean re bonus
