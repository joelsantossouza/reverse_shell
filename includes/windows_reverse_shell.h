/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_reverse_shell.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:50:26 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 19:17:10 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOWS_REVERSE_SHELL_H
# define WINDOWS_REVERSE_SHELL_H

# include <winsock2.h>
# include "linux_reverse_shell.h"

// CLIENT SOCKET CONNETIONS
int		winsock_client_connection(SOCKET *client_fd);

// SERVER SOCKET CONNECTIONS
void	winsock_receive_command_output(SOCKET client_fd);
int		winsock_server_connection(SOCKET *server_fd, SOCKET *client_fd,
			char **client_ip);

#endif
