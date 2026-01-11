/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsock_receive_command_output.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:39:45 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 17:39:57 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <winsock2.h>
#include <stdio.h>

void winsock_receive_command_output(SOCKET client_fd)
{
	char    buffer[4096];
	int     bytes_read;
	u_long  data_available = 0;
	int     wait_count = 0;

	// 1. Give the Windows machine a moment to think and respond
	// Windows cmd.exe is slightly slower than Linux bash
	Sleep(200);

	while (1)
	{
		// 2. Check how many bytes are waiting in the socket buffer
		if (ioctlsocket(client_fd, FIONREAD, &data_available) != 0)
			break;

		if (data_available > 0)
		{
			bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
			if (bytes_read > 0)
			{
				buffer[bytes_read] = '\0';
				printf("%s", buffer);
				fflush(stdout); // Ensure it prints to your screen immediately
			}
			wait_count = 0; // Reset wait if we got data
		}
		else
	{
			// 3. Small delay and retry a few times 
			// This handles slow networks or large command outputs
			Sleep(50);
			wait_count++;
			if (wait_count > 10) // If no data for ~500ms, assume cmd.exe is done
				break;
		}
	}
}
