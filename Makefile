CONTROLLER = controller
TARGET = target

SRCS_CONTROLLER = controller.c
OBJS_CONTROLLER = $(SRCS_CONTROLLER:.c=.o)

SRCS_TARGET = target.c
OBJS_TARGET = $(SRCS_TARGET:.c=.o)

LIBS_DIR = libs
LIBFT = $(LIBS_DIR)/libft/libft.a

CC = cc
FLAGS = -Wall -Wextra -Werror -g
HEADER = reverse_shell.h
INCLUDES = $(addprefix -I, $(LIBS_DIR)/libft)

all: $(CONTROLLER) $(TARGET)

$(CONTROLLER): $(LIBFT) $(OBJS_CONTROLLER)
	$(CC) $(OBJS_CONTROLLER) $(LIBFT) -o $@

$(TARGET): $(OBJS_TARGET)
	$(CC) $(OBJS_TARGET) -o $@

$(LIBFT):
	@if [ ! -d "$(dir $@)" ]; then \
		git clone git@github.com:joelsantossouza/libft.git $(dir $@); \
	fi
	make -C $(dir $@)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS_CONTROLLER)
	rm -f $(OBJS_TARGET)

fclean: clean
	rm -f $(CONTROLLER)
	rm -f $(TARGET)

re: fclean all
