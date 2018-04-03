# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yokartou <yokartou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/12 21:43:25 by yokartou          #+#    #+#              #
#    Updated: 2018/03/14 13:28:35 by yokartou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Wolf3d

CC = clang

CFLAGS = -Wall -Werror -Wextra

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

SRC_DIR = srcs

INC_DIR = incs

OBJ_DIR = objs

LIBS = -I minilibx \
	   -I libft \
	   -L./libft/ -lft

SRC = draw.c \
	  error.c \
	  init.c \
	  key.c \
	  main.c \
	  move.c \
	  ray.c \
	  read.c \
	  texture.c

OBJ = $(SRC:%.c=objs/%.o)

all : objs $(NAME)

objs :
	@mkdir objs

$(NAME): $(OBJ)
	@make -C libft/
	@make -C minilibx
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I $(INC_DIR) $(MLXFLAGS) $(LIBS) # -g -fsanitize=address
	@echo "Wolf3d Done"

objs/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	@make -C libft/ clean
	@make -C minilibx/ clean
	@rm -rf objs

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
