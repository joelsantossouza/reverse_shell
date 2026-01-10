/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:38:07 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/10 21:54:20 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "prompt_command.h"
#include "libft.h"

char	*prompt_command(char **cmdptr, uint64_t *cmdlen, const char *host_ip)
{
	static char	*line = NULL;

	write(STDOUT_FILENO, LOGO_COLOR, LOGO_COLOR_STRLEN);
	write(STDOUT_FILENO, LOGO, LOGO_STRLEN);

	write(STDOUT_FILENO, HOST_IP_COLOR, HOST_IP_COLOR_STRLEN);
	write(STDOUT_FILENO, host_ip, strlen(host_ip));

	write(STDOUT_FILENO, PROMPT_END_COLOR, PROMPT_END_COLOR_STRLEN);
	write(STDOUT_FILENO, PROMPT_END, PROMPT_END_STRLEN);

	write(STDOUT_FILENO, RESET_COLOR, RESET_COLOR_STRLEN);
	*cmdlen = ft_getline(&line, STDIN_FILENO);
	if (*cmdlen <= 0)
		return (NULL);
	*cmdptr = line;
	return (line);
}
