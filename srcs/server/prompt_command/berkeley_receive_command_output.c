/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berkeley_receive_command_output.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 21:47:53 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 17:44:53 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "libft.h"
#include "linux_reverse_shell.h"
#include "prompt_command.h"

void	berkeley_receive_command_output(int client_fd)
{
	static char		*output_line = NULL;
	static uint64_t	output_linelen;

	while (TRUE)
	{
		output_linelen = ft_getline(&output_line, client_fd);
		if (output_line == NULL)
			break ;
		if (strcmp(output_line, REVSHELL_EOF "\n") == 0)
			break ;
		write(STDOUT_FILENO, output_line, output_linelen);
	}
}
