# Quick Reference - MONO Mode Usage

## What Was Added?

### MONO Server (Option 3)
- Simple sequential server without fork()
- Functionally identical to FIFO but with cleaner code
- No zombie process management needed
- Good for learning/testing

### MONO Client (Option 2)
- Makes ONE request then disconnects
- Simpler than normal client
- Good for batch operations or quick queries

---

## Quick Start

### Build
```bash
cd ~/tcp_cl_sr/version2/version3
make clean
make
```

### Run MONO Server
```bash
./server 8080
# Select option: 3
```

### Run MONO Client
```bash
./client localhost 8080
# Select option: 2
# Select service: 1, 2, 3, 4, or 5
# Automatically disconnects after one request
```

---

## Server Mode Comparison

```
Option 1: MULTI-PROCESS (Concurrent)
├─ Uses fork()
├─ Multiple clients at same time
├─ Higher memory usage
└─ Best for: High traffic

Option 2: FIFO (Sequential)
├─ No fork
├─ One client at a time
├─ Simpler than option 1
└─ Best for: Testing

Option 3: MONO (Sequential, No Fork)  ← NEW
├─ No fork
├─ One client at a time
├─ Simplest implementation
└─ Best for: Learning/Testing
```

---

## Client Mode Comparison

```
Option 1: NORMAL CLIENT
├─ Multiple requests per session
├─ Loop until user exits
├─ Longer connections
└─ Best for: Interactive use

Option 2: MONO CLIENT  ← NEW
├─ One request then exit
├─ Quick connection
├─ Minimal interaction
└─ Best for: Batch/Query
```

---

## Test Scenarios

### Scenario 1: Simple MONO-to-MONO
```bash
# Terminal 1
./server 8080
# Choose: 3 (MONO)

# Terminal 2
./client localhost 8080
# Choose: 2 (MONO)
# Choose: 1 (Date)
# Exits automatically

# Run client again for next request
./client localhost 8080
# Choose: 2 (MONO)
# Choose: 2 (Directory)
# Exits automatically
```

### Scenario 2: MONO Clients with FIFO Server
```bash
# Terminal 1
./server 8080
# Choose: 2 (FIFO)

# Terminal 2
./client localhost 8080
# Choose: 2 (MONO)
# Choose: 1 (Date)
# Exits

# Server immediately ready for next client

# Terminal 3
./client localhost 8080
# Choose: 2 (MONO)
# Choose: 3 (File content)
# Exits
```

### Scenario 3: Mixed Client Types
```bash
# Terminal 1
./server 8080
# Choose: 2 (FIFO)

# Terminal 2 - Normal Client (takes 10 seconds, multiple requests)
./client localhost 8080
# Choose: 1 (NORMAL)
# Make several requests
# Choose: 5 to exit

# Terminal 3 - MONO Client (waiting)
./client localhost 8080
# Choose: 2 (MONO)
# When terminal 2 exits, immediately gets served
# Choose: 1 (Date)
# Exits
```

---

## Key Differences at a Glance

| Aspect | FIFO Server | MONO Server |
|--------|-------------|------------|
| **Code** | `while(1) { accept(); handle(); close(); }` | Same |
| **Forking** | No fork | No fork |
| **Zombie** | No zombies | No zombies |
| **Simplicity** | Medium | Highest |
| **Naming** | Historical (queue-like) | Mono (single-threaded style) |

---

## Files Modified

1. **server.c**
   - Added `run_mono_server()` function
   - Added option 3 to menu
   - Added case 3 to switch

2. **client.c**
   - Added client mode selection menu
   - Routes to `run_normal_client()` or `run_mono_client()`

3. **clientdef.h**
   - Added `run_normal_client()` function
   - Added `run_mono_client()` function

4. **README.md**
   - Updated overview
   - Added MONO server explanation
   - Added client mode explanation
   - Added usage examples

5. **NEW: CHANGES_MONO_MODE.md**
   - Detailed change documentation

---

## Why Two Sequential Modes (FIFO and MONO)?

1. **Educational**: Show different sequential approaches
2. **Historical**: FIFO is traditional naming
3. **Clarity**: MONO emphasizes single-threaded nature
4. **Learning**: Both do same thing, different mental models
5. **Simplicity**: MONO is simplest to understand

---

## Common Questions

**Q: Can I run multiple MONO clients at once?**
- A: Yes, but they queue. First client gets served, others wait.

**Q: Does MONO client waste connection?**
- A: No, it's actually efficient. Close immediately after use.

**Q: Should I use MONO for production?**
- A: No. Use multi-threaded, multi-process, or async servers.

**Q: What's the performance difference between FIFO and MONO?**
- A: Negligible. MONO saves fork() overhead but still sequential.

**Q: Can MONO server handle 1000s of clients?**
- A: Not simultaneously. It handles them one-at-a-time in a queue.

---

## Complete Server Menu

```
========================================
     TCP SERVER - MODE SELECTION
========================================
1. Multi-process (Concurrent clients)
   • Handles multiple clients at same time
   • Uses fork() for each client
   • Higher memory usage
   • Requires zombie cleanup

2. FIFO/Sequential (One client at a time)
   • Handles clients in sequence
   • No forking
   • Simpler than option 1
   
3. MONO (Single client, no fork) ← NEW
   • Simplest sequential server
   • No forking required
   • Same behavior as FIFO
   • Best for learning

========================================
```

---

## Complete Client Menu

```
========================================
   TCP CLIENT - MODE SELECTION
========================================
1. Normal client
   • Multiple requests per session
   • Loop until user chooses exit
   • Better for interactive use

2. MONO client (simple single session) ← NEW
   • One request then disconnect
   • Quick and simple
   • Better for batch operations

========================================
```

---

## Execution Flow Diagrams

### MONO Server Flow
```
START
  ↓
Listen on port
  ↓
Accept client connection
  ↓
Handle client (all requests)
  ↓
Close connection
  ↓
Back to "Accept" → Handle multiple clients sequentially
```

### MONO Client Flow
```
START
  ↓
Connect to server
  ↓
Display menu (once)
  ↓
Get one user input
  ↓
Send to server & receive response
  ↓
Display response
  ↓
Close connection & EXIT
```

### NORMAL Client Flow
```
START
  ↓
Connect to server
  ↓
Display menu
  ↓
Loop:
  ├─ Get user input
  ├─ Send to server & receive response
  ├─ Display response
  └─ Repeat until user selects EXIT
  ↓
Close connection & EXIT
```

---

## Testing Checklist

- [ ] Compile with: `make clean && make`
- [ ] Start MONO server: `./server 8080` → choose 3
- [ ] Connect with MONO client: `./client localhost 8080` → choose 2
- [ ] Try all 5 menu options (1-5)
- [ ] Verify auto-disconnect after each request
- [ ] Try MONO server with normal clients
- [ ] Try normal clients with MONO server
- [ ] Test rapid MONO client connections
- [ ] Verify no errors or memory leaks
- [ ] Compare FIFO and MONO behavior (should be identical)

---

## Summary

✓ **MONO Server**: New simplified sequential server option
✓ **MONO Client**: New single-request client option
✓ **Full backward compatibility**: Existing options 1-2 still work
✓ **Educational value**: Clear example of simple sequential patterns
✓ **No breaking changes**: Can still use multi-process or FIFO modes
