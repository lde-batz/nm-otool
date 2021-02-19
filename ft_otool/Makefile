# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/15 16:25:16 by lde-batz          #+#    #+#              #
#    Updated: 2021/02/15 14:31:50 by lde-batz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_otool

CC = gcc

SRC += 	main.c
SRC += 	error.c
SRC += 	ft_otool.c
SRC += 	handle_32.c
SRC += 	handle_64.c
SRC += 	handle_arch.c
SRC += 	handle_fat_32.c
SRC += 	handle_fat_64.c
SRC += 	parsing.c
SRC += 	print_output.c
SRC += 	check.c
SRC += 	tools.c

SRC_DIR = srcs/

OBJ_DIR = objects/

OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

SRC := $(addprefix $(SRC_DIR), $(SRC))

INC = includes

INCLUDES = $(INC)/ft_otool.h

LIB = ../libft

INC_FLAG = -I$(INC) -I$(LIB)

LIB_FLAG = -L ./$(LIB) -lft

#Compile debug flags
CFLAGS += -Wall -Wextra
ifeq ($(d), 1)
	CFLAGS += -g3 -fsanitize=address,undefined
else ifeq ($(d), 2)
	CFLAGS += -g3 -fsanitize=address,undefined
	CFLAGS += -Wpadded -Wpedantic
endif
ifneq ($(err), no)
	CFLAGS += -Werror
endif

GCC = $(CC) $(CFLAGS)

.SILENT:

all: lib $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(INC_FLAG) -o $(NAME) $(SRC) $(LIB_FLAG)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Create ft_otool"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES) $(LIB)/libft.a
	mkdir -p $(OBJ_DIR)
	$(GCC) $(INC_FLAG)  -c $< -o $@
	printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

lib:
	make -C $(LIB)

clean:
	make -C $(LIB) clean
	rm -f $(OBJ)
	rm -Rf $(OBJ_DIR)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean ft_otool"

fclean: clean
	make -C $(LIB) fclean
	rm -f $(NAME)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fclean ft_otool"

re: fclean all

.PHONY: all clean fclean re

