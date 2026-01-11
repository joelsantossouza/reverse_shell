/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berkeley_server_connection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:21:40 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 20:08:34 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include "linux_reverse_shell.h"

int	berkeley_server_connection(int *server_fd, int *client_fd,
								char **client_ip_ptr)
{
	static char			client_ip[INET_ADDRSTRLEN];
	struct sockaddr_in	addr;
	socklen_t			addr_len;
	int					opt;

	opt = 1;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(SERVER_PORT);
	*server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*server_fd == -1)
		return (errno);
	if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEALL, &opt, sizeof(opt)) != 0)
		return (close(*server_fd), errno);
	if (bind(*server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return (close(*server_fd), errno);
	if (listen(*server_fd, BACKLOG_MAXIMUM) == -1)
		return (close(*server_fd), errno);
	addr_len = sizeof(addr);
	*client_fd = accept(*server_fd, (struct sockaddr *)&addr, &addr_len);
	if (*client_fd == -1)
		return (close(*server_fd), errno);
	if (inet_ntop(AF_INET, &addr.sin_addr, client_ip, INET_ADDRSTRLEN) == 0)
		strlcpy(client_ip, "None", INET_ADDRSTRLEN);
	*client_ip_ptr = client_ip;
	return (SUCCESS);
}
