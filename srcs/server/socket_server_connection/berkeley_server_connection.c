/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berkeley_server_connection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:21:40 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/10 16:11:14 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include "reverse_shell.h"

# define SO_REUSEALL		(SO_REUSEADDR | SO_REUSEPORT)
# define BACKLOG_MAXIMUM	3

int	berkeley_server_connection(int *server_fd, int *client_fd)
{
	static char			client_ip_address[INET_ADDRSTRLEN];
	int					opt;
	struct sockaddr_in	server_addr;
	socklen_t			addr_len;

	opt = 1;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	addr_len = sizeof(server_addr);
	*server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*server_fd == -1)
		return (errno);
	if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEALL, &opt, sizeof(opt) != 0))
		return (close(*server_fd), errno);
	if (bind(*server_fd, (struct sockaddr *)&server_addr, addr_len) < 0)
		return (close(*server_fd), errno);
	if (listen(*server_fd, BACKLOG_MAXIMUM) == -1)
		return (close(*server_fd), errno);
	*client_fd = accept(*server_fd, (struct sockaddr *)&server_addr, &addr_len);
	if (*client_fd == -1)
		return (close(*server_fd), errno);
	if (inet_ntop() == NULL)
	return (SUCCESS);
}
