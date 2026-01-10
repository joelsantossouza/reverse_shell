# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/10 19:15:36 by joesanto          #+#    #+#              #
#    Updated: 2026/01/10 19:51:41 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g
SRCS_DIR = srcs
INFECT_PROGRAM = $(SRCS_DIR)/program_test.c

# ----------------------------------- BINS ----------------------------------- #
BIN_DIR = bin
PROGRAM_NAME := $(notdir $(basename $(INFECT_PROGRAM)))

# CLIENT
LINUX_INFECTED_PROGRAM = $(BIN_DIR)/linux_infected_$(PROGRAM_NAME)

# SERVER
BERKELEY_SERVER = $(BIN_DIR)/berkeley_server

# ---------------------------------- SOURCES --------------------------------- #

# CLIENT
LINUX_CLIENT_DIR = $(SRCS_DIR)/client
BACKDOORS_DIR = $(SRCS_DIR)/backdoors
SOCKET_CONNECTION_DIR = $(SRCS_DIR)/socket_client_connection

SOCKET_CONNECTION_SRCS = $(addprefix $(SOCKET_CONNECTION_DIR)/, \
						 berkeley_client_connection.c \
)
LINUX_CLIENT_OBJS += $(SOCKET_CONNECTION_SRCS:.c=.o) $(INFECT_PROGRAM:.c=.o)

# -------------------------------- COMPILATION ------------------------------- #

all: $(LINUX_INFECTED_PROGRAM)

$(LINUX_INFECTED_PROGRAM): $(LINUX_CLIENT_OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(LINUX_CLIENT_OBJS)

fclean: clean
	rm -f $(BIN_DIR)

re: fclean all
