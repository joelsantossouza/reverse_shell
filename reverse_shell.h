#ifndef REVERSE_SHELL_H
# define REVERSE_SHELL_H

# if defined(_WIN32)
#  ifndef _WIN32_WINT
#   define _WIN32_WINT	0x0600
#  endif
#  include <winsock2.h>
#  include <wc2tcpip.h>
#  pragma comment(lib, ws2_32.lib)
#  define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#  define CLOSESOCKET(s) (closesocket(s))
#  define GETSOCKETERRNO WASGetLastError()

# else
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <unistd.h>
#  include <fcntl.h>
#  include <string.h>
#  include <errno.h>
#  define SOCKET int
#  define ISVALIDSOCKET(s) ((s) >= 0)
#  define CLOSESOCKET(s) (close(s))
#  define GETSOCKETERRNO errno
# endif

# ifndef PORT
#  define PORT			4444
# endif

# ifndef SERVER_HOST
#  define SERVER_HOST	"127.0.0.1"
# endif

# define RED	"\e[0;31m"
# define RESET	"\e[0m"

#endif
