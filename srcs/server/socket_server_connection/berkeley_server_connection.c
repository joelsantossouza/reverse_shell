/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berkeley_server_connection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:21:40 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 12:17:10 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include "linux_reverse_shell.h"

int	berkeley_server_connection(int *server_fd, int *client_fd, char **client_ip)
{
	static char			client_ip_address[INET_ADDRSTRLEN];
	struct sockaddr_in	server_addr;
	struct sockaddr_in	client_info;
	socklen_t			addr_len;
	int					opt;

	opt = 1;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	*server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*server_fd == -1)
		return (errno);
	if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEALL, &opt, sizeof(opt)) != 0)
		return (close(*server_fd), errno);
	if (bind(*server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		return (close(*server_fd), errno);
	if (listen(*server_fd, BACKLOG_MAXIMUM) == -1)
		return (close(*server_fd), errno);
	addr_len = sizeof(client_info);
	*client_fd = accept(*server_fd, (struct sockaddr *)&client_info, &addr_len);
	if (*client_fd == -1)
		return (close(*server_fd), errno);
	if (inet_ntop(AF_INET, &client_info.sin_addr, client_ip_address, INET_ADDRSTRLEN) == NULL)
		strlcpy(client_ip_address, "None", INET_ADDRSTRLEN);
	*client_ip = client_ip_address;
	return (SUCCESS);
}
