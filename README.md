# TCP Multi-Server Multi-Client Application

## Project Overview

This is a comprehensive TCP client-server application that demonstrates three different server architectures:
1. **Multi-process Server** (Concurrent): Handles multiple clients simultaneously using process forking
2. **FIFO Server** (Sequential): Handles clients one at a time in a First-In-First-Out manner
3. **MONO Server**: Single client handler, no fork - simpler sequential processing

The application also provides two client modes:
1. **Normal Client**: Allows multiple interactions with the server in a session
2. **MONO Client**: Simple single-session client that makes one request and disconnects

The application provides various services including date/time display, directory listing, file content viewing, and session time tracking.

---

## Architecture

### Server Components

#### 1. **server.c** - Main Server Entry Point
```c
main(int argc, char *argv[])
```
- **Purpose**: Entry point that allows user to select server mode
- **Flow**:
  1. Validates command-line arguments (port number required)
  2. Displays server mode selection menu
  3. Creates and configures socket
  4. Binds to specified port
  5. Starts listening for connections
  6. Launches selected server mode (multi-process or FIFO)

**Key Functions**:
- `run_multiprocess_server()`: Implements concurrent client handling using fork()
- `run_fifo_server()`: Implements sequential client handling
- `run_mono_server()`: Implements mono server (single client, no fork)

#### 2. **serverimp.c** - Server Implementation
Contains all server logic and client handling functions.

**Socket Setup Functions**:
```c
void new_socket()
```
- Creates a TCP socket using `socket(AF_INET, SOCK_STREAM, 0)`
- AF_INET = IPv4, SOCK_STREAM = TCP protocol
- Stores socket file descriptor in global `sockfd`
