/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_command_output.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 21:47:53 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/10 21:58:10 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include "reverse_shell.h"
#include "libft.h"

void	receive_command_output(int client_fd)
{
	static char		*output_line = NULL;
	static uint64_t	output_linelen;

	while (TRUE)
	{
		output_linelen = ft_getline(&output_line, client_fd);
		if (output_line == NULL)
			break ;
		write(STDOUT_FILENO, output_line, output_linelen);
	}
}
