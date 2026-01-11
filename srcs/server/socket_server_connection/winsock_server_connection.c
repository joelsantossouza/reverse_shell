/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsock_server_connection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:56:52 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 01:00:43 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <winsock2.h>
#include <ws2tcpip.h>
#include "windows_reverse_shell.h"

int	winsock_server_connection(SOCKET *server_fd, SOCKET *client_fd, char **client_ip)
{
	static char			client_ip_address[INET_ADDRSTRLEN];
	int					opt;
	struct sockaddr_in	server_addr;
	struct sockaddr_in	client_info;
	int					addr_len;
	WSADATA				wsa;

	opt = 1;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return (WSACleanup(), WSAGetLastError());
	*server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*server_fd == INVALID_SOCKET)
		return (WSACleanup(), WSAGetLastError());
	if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) == SOCKET_ERROR)
	{
		int	err = WSAGetLastError();
		closesocket(*server_fd);
		return (WSACleanup(), err);
	}
	if (bind(*server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		int	err = WSAGetLastError();
		closesocket(*server_fd);
		return (WSACleanup(), err);
	}
	if (listen(*server_fd, BACKLOG_MAXIMUM) == SOCKET_ERROR)
	{
		int	err = WSAGetLastError();
		closesocket(*server_fd);
		return (WSACleanup(), err);
	}
	addr_len = sizeof(client_info);
	*client_fd = accept(*server_fd, (struct sockaddr *)&client_info, &addr_len);
	if (*client_fd == INVALID_SOCKET)
	{
		int	err = WSAGetLastError();
		closesocket(*server_fd);
		return (WSACleanup(), err);
	}
	u_long	mode = 1;
	if (ioctlsocket(*client_fd, FIONBIO, &mode) != NO_ERROR)
	{
		int err = WSAGetLastError();
        closesocket(*client_fd);
        closesocket(*server_fd);
        return (WSACleanup(), err);
	}
	if (inet_ntop(AF_INET, &client_info.sin_addr, client_ip_address, INET_ADDRSTRLEN) == NULL)
        strncpy_s(client_ip_address, INET_ADDRSTRLEN, "None", _TRUNCATE);
	*client_ip = client_ip_address;
	return (SUCCESS);
}
