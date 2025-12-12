#include <asm-generic/socket.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "reverse_shell.h"
#include "libft/libft.h"
#include <fcntl.h>

int	error(char *message, int exit_code)
{
	int	message_len;

	message_len = strlen(message);
	write(2, message, message_len);
	write(2, "\n", 1);
	return (exit_code);
}

int	create_server(int *fd, int *client_fd)
{
	int 				opt;
	socklen_t			addr_len;
	struct sockaddr_in addr;

	*fd = socket(AF_INET, SOCK_STREAM, 0);
	addr_len = sizeof(addr);
	if (*fd < 0)
		return (error("Failed opening socket", 1));
	opt = 1;
	if (setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0)
	{
		close(*fd);
		return (error("failed setting socket options", 1));
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	if (bind(*fd, (struct sockaddr *)&addr, addr_len) < 0)
	{
		close(*fd);
		return (error("Could no bind to address", 1));
	}
	if (listen(*fd, 3) < 0)
	{
		close(*fd);
		return (error("Failed to listen for connections", 1));
	}
	*client_fd = accept(*fd, (struct sockaddr *)&addr, &addr_len);
	if (*client_fd < 0)
	{
		close(*fd);
		return (error("Failed accepting the connection", 1));
	}
	return (0);
}

int	disable_blocking_mode(int socket_fd)
{
	int	fd_flags;

	fd_flags = fcntl(socket_fd, F_GETFL, 0);
	fd_flags |= O_NONBLOCK;
	return (fcntl(socket_fd, F_SETFL, fd_flags));
}

int	main(void)
{
	int	server_fd;
	int	client_fd;
	char *line;

	if (create_server(&server_fd, &client_fd) != 0)
		return (1);
	if (disable_blocking_mode(client_fd) != 0)
		return (close(server_fd), close(client_fd), 1);
	line = 0;
	while (1)
	{
		write(1, RED, 7);
		write(1, "reverse_shell$ ", 15);
		write(1, RESET, 4);
		if (ft_getline(&line, 0) <= 0)
			break ;
		write(client_fd, line, strlen(line));
		while (ft_getline(&line, client_fd) > 0)
			write(1, line, strlen(line));
	}
	return (0);
}
