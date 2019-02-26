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

FLAGS = -c -Wall -Wextra -Werror -O3
CC = gcc

LIBFT_DIR = libft
LIBS = -L $(LIBFT_DIR) -lft
LEM-IN_HEAD = lem-in.h

INCLUDES = -I $(LEM-IN_HEAD) -I $(LIBFT_DIR)/includes

SRC = 	main.c parse_data.c push.c ants_transmission.c fast_search.c chained_room_util.c \
        manage_print.c

OBJ = $(patsubst %.c, %.o, $(SRC))

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
OFF = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) $< -o $@

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling lem-in project...\n$(OFF)"
	@echo "$(YELLOW)Compiling libft...$(OFF)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)libft.a was created.$(OFF)"
	@$(CC) $(OBJ) $(LIBS) -o $@
	@echo "$(GREEN)lem-in completed!\n$(OFF)"
	@echo "$(GREEN)usage: ./lem-in [-color | -lines | -cmt] < [map]$(OFF)"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJ)
	@rm -f filler.trace
	@echo "$(RED)libft.a was removed$(OFF)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@rm -f $(OBJ)
	@rm -f filler.trace
	@echo "$(RED)All objects were removed$(OFF)"

re: fclean all
