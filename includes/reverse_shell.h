/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_shell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:48:25 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/10 16:02:29 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_SHELL_H
# define REVERSE_SHELL_H

# define SUCCESS	0

# ifndef PORT
#  define PORT		4242
# endif

# ifndef SERVER_IP
#  define SERVER_IP	"127.0.0.1"
# endif

int	berkeley_server_connection(int *server_fd, int *client_fd);

#endif
