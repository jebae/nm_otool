# name
NAME = ft_otool

# path
SRC_DIR = ./srcs
INC_DIR = ./includes
OBJ_DIR = ./objs
LIB_DIR = ../libs
LIBFT = $(LIB_DIR)/libft
FT_PRINTF = $(LIB_DIR)/ft_printf
LIB_SHARED = ../shared

# compiler
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I $(INC_DIR)\
	-I $(LIBFT)/includes\
	-I $(FT_PRINTF)/includes\
	-I $(LIB_SHARED)
LIBS = -L $(LIBFT) -lft\
	-L $(FT_PRINTF) -lftprintf\
	-L $(LIB_SHARED) -lshared

# srcs
SRCS = text_section.c

TEST = ./srcs/*.test.cpp

# objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# command
def = ''

test:
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(LIB_SHARED)
	g++\
		-Wall -Wextra -std=c++11\
		$(def)\
		-lgtest\
		$(LIBS)\
		$(INCLUDES)\
		$(filter-out srcs/main.c, $(wildcard srcs/*.c)) $(TEST)\
		-o $@

.PHONY: test
