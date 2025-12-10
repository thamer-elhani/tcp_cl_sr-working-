# TCP Multi-Server Multi-Client Application (Working Version)

## Project Overview

This is a comprehensive TCP client-server application that demonstrates three different server architectures:

1. **Multi-process Server** (Concurrent) - Handles multiple clients simultaneously using process forking
2. **FIFO Server** (Sequential) - Handles clients one at a time in a First-In-First-Out manner
3. **MONO Server** - Single client handler, no fork - simpler sequential processing

### Client Modes

1. **Normal Client** - Allows multiple interactions with the server in a session
2. **MONO Client** - Simple single-session client that makes one request and disconnects

## Features

✅ **MONO Server Mode** - Simplified sequential server without fork()
✅ **MONO Client Mode** - Single-request client mode
✅ **Dynamic File Selection** - Option 3 accepts file paths from ./data/
✅ **Full Backward Compatibility** - Original modes still available
✅ **Comprehensive Documentation** - Multiple guides and references

## Quick Start

### Build the Project

```bash
cd version3
make clean && make
```

### Run MONO Server

```bash
./server 8080
# When prompted, select: 3 (MONO mode)
```

### Run MONO Client

```bash
./client localhost 8080
# When prompted, select: 2 (MONO client)
# When prompted, select service: 1-5
```

## Menu Structure

### Server Modes

```
1. Multi-process (Concurrent clients)
2. FIFO/Sequential (One client at a time)
3. MONO (Single client, no fork)
```

### Client Modes

```
1. Normal client
2. MONO client (simple single session)
```

### Available Services

```
1. Show date and time
2. List directory files
3. Display file content (specify path)
4. Show session elapsed time
5. Exit
```

## Version History

### Version 3 (Latest - Working)

- ✅ Added MONO server mode (Option 3)
- ✅ Added MONO client mode (Option 2)
- ✅ Dynamic file selection in Option 3
- ✅ Comprehensive documentation
- ✅ Full backward compatibility

## Author

Thamer El-hani

## License

MIT License
