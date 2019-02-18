# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/04 16:22:11 by dlenskyi          #+#    #+#              #
#    Updated: 2019/02/15 18:20:56 by dlenskyi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra -Werror -O3
CC = gcc

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_HEAD = $(LIBFT_DIR)includes/
LEM-IN_HEAD = lem-in.h

INCLUDES = -I$(LEM-IN_HEAD) -I$(LIBFT_HEAD)

SRC = 	main.c parse_data.c push.c ants_transmission.c fast_search.c chained_room_util.c

OBJ = $(patsubst %.c, %.o, $(SRC))

RED = \x1B[31m
GREEN = \x1B[32m
YELLOW = \x1B[33m
OFF = \x1B[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(INCLUDES) $(LIBFT) $(OBJ) -o $(NAME)
	@echo "$(GREEN)lem-in completed!\n$(OFF)"
	@echo "$(GREEN)usage example: ./lem-in < [map]$(OFF)"

%.o: %.c $(LEM-IN_HEAD)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Compiling lem-in project...\n$(OFF)"
	@echo "$(YELLOW)Compiling libft...$(OFF)"
	@$(MAKE) -sC $(LIBFT_DIR)
	@echo "$(GREEN)libft.a was created.$(OFF)"

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -f $(OBJ)
	@rm -f filler.trace
	@echo "$(RED)libft.a was removed$(OFF)"

fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)
	@rm -f $(OBJ)
	@rm -f filler.trace
	@echo "$(RED)All objects were removed$(OFF)"

re: fclean all
