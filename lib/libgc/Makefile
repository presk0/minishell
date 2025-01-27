CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g

LIBFT_DIR = ../libft
SRC_DIR = src
OBJ_DIR = obj
INCLUDES = -I include -I $(LIBFT_DIR)/include
FT_FLAGS = -lft -L $(LIBFT_DIR)

FILES = gc.c strcat.c strdup.c

OBJS = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

NAME = libgc.a

$(NAME): $(OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(FT_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean $(NAME)

.PHONY: all clean fclean re
