/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berkeley_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:00:43 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/10 16:06:52 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "reverse_shell.h"

int	main(void)
{
	int		server_fd;
	int		client_fd;
	char	*client_ip;

	if (berkeley_server_connection(&server_fd, &client_fd, &client_ip) != 0)
	{
		fprintf(stderr, "%s", strerror(errno));
		return (1);
	}
}
