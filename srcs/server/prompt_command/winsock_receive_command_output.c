/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsock_receive_command_output.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:39:45 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 19:43:38 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <winsock2.h>
#include <stdio.h>

#define BUFFER_SIZE	4096

void	winsock_receive_command_output(SOCKET client_fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	static u_long	data_available;
	static int		wait_count;
	int				bytes_read;

	Sleep(200);
	while (TRUE)
	{
		if (ioctlsocket(client_fd, FIONREAD, &data_available) != 0)
			break ;
		if (data_available <= 0)
		{
			Sleep(50);
			if (++wait_count > 10)
				break ;
			continue ;
		}
		bytes_read = recv(client_fd, buffer, BUFFER_SIZE, 0);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			printf("%s", buffer);
			fflush(stdout);
		}
		wait_count = 0;
	}
}
