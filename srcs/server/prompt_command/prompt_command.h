/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_command.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:47 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/10 17:07:25 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_COMMAND_H
# define PROMPT_COMMAND_H

// COLORS
#define RED						"\e[0;31m"
#define GREEN					"\e[0;32m"
#define RESET_COLOR				"\e[0m"

// COLORS STRLEN
#define RED_STRLEN				7
#define GREEN_STRLEN			7
#define RESET_COLOR_STRLEN		4

// CUSTOMIZED PROMPT
#define LOGO					"reverse_shell@"
#define LOGO_STRLEN				14
#define LOGO_COLOR				RED
#define LOGO_COLOR_STRLEN		RED_STRLEN

#define HOST_IP_COLOR			GREEN
#define HOST_IP_COLOR_STRLEN	GREEN_STRLEN

#define PROMPT_END				"$> "
#define PROMPT_END_STRLEN		3
#define PROMPT_END_COLOR		RED
#define PROMPT_END_COLOR_STRLEN	RED_STRLEN

#endif
