/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_reverse_shell.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:48:25 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 19:16:42 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINUX_REVERSE_SHELL_H
# define LINUX_REVERSE_SHELL_H

# include <stdint.h>

// UTILS
# define TRUE		1
# define FALSE		0
# define SUCCESS	0

// CONNECTION INFORMATIONS
# ifndef PORT
#  define PORT		4242
# endif

# ifndef SERVER_IP
#  define SERVER_IP	"127.0.0.1"
# endif

# define SO_REUSEALL		15
# define BACKLOG_MAXIMUM	3

// CLIENT SOCKET CONNECTIONS
int		berkeley_client_connection(int	*client_fd);

// SERVER SOCKET CONNECTIONS
int		berkeley_server_connection(int *server_fd, int *client_fd,
			char **client_ip);

#endif
