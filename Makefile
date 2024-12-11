NAME := pipex

CC := cc
CFLAGS := -Wextra -Wall -Werror

LIBFT_DIR := ./lib/libft
LIBFT := $(LIBFT_DIR)/libft.a
BTREE_DIR := ./lib/btree
BTREE := $(BTREE_DIR)/btree.a

LIBS :=  $(LIBFT) $(BTREE_DIR)
HEADERS := -I ./include -I $(LIBMLX_DIR)/include -I $(BTREE_DIR)

SRCS := src/main.c src/utils.c
OBJS := $(SRCS:.c=.o)

all: make_libft $(NAME)

make_libft:
	@make -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) $(OBJS) $(LIBS) -o $(NAME)

debug: $(OBJS)
	@$(CC) -g $(HEADERS) src/*.c $(LIBS) -o pouet
	lldb pouet
	rm pouet

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re make_libft
