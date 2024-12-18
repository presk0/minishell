NAME = minishell

LIBRARIES = btree gc ft
LIB_NAMES = $(addprefix lib, $(LIBRARIES))

LIB_DIR = ./lib

INCLUDE_DIRS = ./include
INCLUDE_DIRS += $(addsuffix /include,$(addprefix $(LIB_DIR)/,$(LIB_NAMES)))

CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline -g3
LDFLAGS = $(addprefix -L$(LIB_DIR)/lib,$(LIBRARIES))
LDLIBS = $(addprefix -l,$(LIBRARIES))
LIBS = $(addprefix $(LIB_DIR)/,$(LIBRARIES))
INCLUDES = $(addprefix -I,$(INCLUDE_DIRS))

SRC_DIR =	./src
SRCS =	$(wildcard $(SRC_DIR)/*.c)	\
		$(wildcard ./src/ft_env/*.c)	\

all: make_libs $(NAME)

$(NAME):
	echo $(INCLUDES)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(SRCS) -o $@ $(LDLIBS)



make_libs:
	@for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib; \
	done

clean:
	@for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib clean; \
	done

fclean: clean
	@for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib fclean; \
	done
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re make_libs
