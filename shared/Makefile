# name
NAME = libshared.so

# path
OBJ_DIR = ./objs
LIB_DIR = ../libs
LIBFT = $(LIB_DIR)/libft
FT_PRINTF = $(LIB_DIR)/ft_printf

# compiler
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fPIC
INCLUDES = -I .\
	-I $(LIBFT)/includes\
	-I $(FT_PRINTF)/includes
LIBS = -L $(LIBFT) -lft\
	-L $(FT_PRINTF) -lftprintf

# srcs
SRCS = file.c

TEST = ./*.test.cpp

# objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# compile
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# command
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -shared -o $@ $(OBJS)

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

def = ''

test:
	$(MAKE) -C $(LIBFT)
	g++\
		-Wall -Wextra -std=c++11\
		$(def)\
		-lgtest\
		$(LIBS)\
		$(INCLUDES)\
		$(SRCS) $(TEST)\
		-o $@

.PHONY: all clean re fclean test
