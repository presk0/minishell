NAME = minishell

LIBRARIES = btree gc ft
LIB_NAMES = $(addprefix lib, $(LIBRARIES))

LIB_DIR = ./lib

INCLUDE_DIRS = ./include
INCLUDE_DIRS += $(addsuffix /include,$(addprefix $(LIB_DIR)/,$(LIB_NAMES)))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -g3
LFLAGS = -lreadline
LDFLAGS = $(addprefix -L$(LIB_DIR)/lib,$(LIBRARIES))
LDLIBS = $(addprefix -l,$(LIBRARIES))
LIBS = $(addprefix $(LIB_DIR)/,$(LIBRARIES))
INCLUDES = $(addprefix -I,$(INCLUDE_DIRS))

SRCS =	$(wildcard ./src/*.c)	\
		$(wildcard ./src/ft_env/*.c)	\
#		$(wildcard ./src/exec/*.c)	\
#		$(wildcard ./src/exec/builtins/*.c)	\

OBJS = $(SRCS:.c=.o)

all: make_libs $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS) $(LFLAGS)

make_libs:
	for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib; \
	done

clean:
	for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib clean; \
	done
	rm -rf $(OBJS)

fclean: clean
	for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib fclean; \
	done
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re make_libs
