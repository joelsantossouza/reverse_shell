/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_command.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:47 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 15:31:42 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_COMMAND_H
# define PROMPT_COMMAND_H

# include <stdint.h>

// COLORS
# define RED						"\e[0;31m"
# define GREEN						"\e[0;32m"
# define WHITE						"\e[0;37m"
# define RESET_COLOR				"\e[0m"

// COLORS STRLEN
# define RED_STRLEN					7
# define GREEN_STRLEN				7
# define WHITE_STRLEN				7
# define RESET_COLOR_STRLEN			4

// CUSTOMIZED PROMPT
# define LOGO						"reverse_shell@"
# define LOGO_STRLEN				14
# define LOGO_COLOR					RED
# define LOGO_COLOR_STRLEN			RED_STRLEN

# define HOST_IP_COLOR				GREEN
# define HOST_IP_COLOR_STRLEN		GREEN_STRLEN

# define PROMPT_END					"$> "
# define PROMPT_END_STRLEN			3
# define PROMPT_END_COLOR			WHITE
# define PROMPT_END_COLOR_STRLEN	WHITE_STRLEN

// PROMPT CONTROL
# define REVSHELL_EOF				"<END_OF_FILE>"

# define SEND_EOF					";echo -e \'\n" REVSHELL_EOF "\'\n"
# define SEND_EOF_STRLEN			26

// PROTOTYPES
char	*prompt_command(char **cmdptr, uint64_t *cmdlen, const char *host_ip);
void	receive_command_output(int client_fd);

#endif
