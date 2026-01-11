/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsock_server_connection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:56:52 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 19:46:19 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <winsock2.h>
#include <ws2tcpip.h>
#include "windows_reverse_shell.h"

int	winsock_server_connection(SOCKET *server_fd, SOCKET *client_fd,
								char **client_ip)
{
	static char			client_ip_address[INET_ADDRSTRLEN];
	struct sockaddr_in	addr;
	int					addr_len;
	int					opt;

	opt = 1;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	*server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*server_fd == INVALID_SOCKET)
		return (1);
	if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) == SOCKET_ERROR)
		return (closesocket(*server_fd), 1);
	if (bind(*server_fd, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
		return (closesocket(*server_fd), 1);
	if (listen(*server_fd, BACKLOG_MAXIMUM) == SOCKET_ERROR)
		return (closesocket(*server_fd), 1);
	addr_len = sizeof(addr);
	*client_fd = accept(*server_fd, (struct sockaddr *)&addr, &addr_len);
	if (*client_fd == INVALID_SOCKET)
		return (closesocket(*server_fd), 1);
	if (inet_ntop(AF_INET, &addr.sin_addr, client_ip_address, INET_ADDRSTRLEN) == NULL)
    	strncpy_s(client_ip_address, INET_ADDRSTRLEN, "None", _TRUNCATE);
	*client_ip = client_ip_address;
	return (SUCCESS);
}
