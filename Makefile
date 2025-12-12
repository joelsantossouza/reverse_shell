CONTROLLER = controller
TARGET_LINUX = target_linux
TARGET_WINDOWS = target_windows.exe

SRCS_CONTROLLER = controller.c
OBJS_CONTROLLER = $(SRCS_CONTROLLER:.c=.o)

SRCS_TARGET = target.c
OBJS_TARGET = $(SRCS_TARGET:.c=.o)

LIBS_DIR = libs
LIBFT = $(LIBS_DIR)/libft/libft.a

CC = gcc
CC_WIN = i686-w64-mingw32-gcc-win32
FLAGS = -Wall -Wextra -Werror -g
HEADER = reverse_shell.h
INCLUDES = $(addprefix -I, $(LIBS_DIR)/libft)

all: $(CONTROLLER) $(TARGET_LINUX) $(TARGET_WINDOWS)

$(CONTROLLER): $(LIBFT) $(OBJS_CONTROLLER)
	$(CC) $(OBJS_CONTROLLER) $(LIBFT) -o $@

$(TARGET_LINUX): $(OBJS_TARGET)
	$(CC) $(OBJS_TARGET) -o $@

$(TARGET_WINDOWS): $(SRCS_TARGET)
	$(CC_WIN) $^ -lws2_32 -o $@

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
	rm -rf $(LIBS_DIR)

re: fclean all
