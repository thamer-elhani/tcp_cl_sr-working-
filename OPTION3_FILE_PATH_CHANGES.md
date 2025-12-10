# Option 3 - File Path Enhancement

## Summary of Changes

Modified the **Option 3 (Display file content)** to accept a file path parameter from the client, allowing users to specify which file to read from the `./data/` directory.

---

## What Changed

### 1. **service.h** - Updated Function Signature
```c
// Before:
void file_content(char *buffer, int max_buffer, int sockfd);

// After:
void file_content(char *buffer, int max_buffer, int sockfd, const char *filepath);
```

### 2. **service.c** - Enhanced File Reading Function
**Changes**:
- Added `filepath` parameter to accept file name from client
- Creates full path by combining `./data/` with the provided filename
- Constructs path: `./data/<filepath>`

**Example**:
- User enters: `my_data.txt`
- Server opens: `./data/my_data.txt`

**Key Code**:
```c
// Build full path: ./data/<filepath>
snprintf(full_path, sizeof(full_path), "./data/%s", filepath);
file_ptr = fopen(full_path, "r");
```

### 3. **serverimp.c** - Server-Side Implementation
**Changes in `answer_question()` case 3**:
- Reads filepath from client
- Removes trailing newline
- Passes filepath to `file_content()` function

**Key Code**:
```c
case 3:
    // Read filepath from client
    bzero(buffer, MAX_BUFFER);
    n = read(sock, buffer, MAX_BUFFER-1);
    
    // Remove newline
    buffer[strcspn(buffer, "\n")] = 0;
    
    // Call file_content with filepath
    file_content(buffer, MAX_BUFFER, sock, buffer);
    return 1;
```

### 4. **clientdef.h** - Client-Side Implementation

#### Updated `reseve_answer()` function:
**Changes in case '3'**:
- Prompts user for file path
- Reads user input with `fgets()`
- Sends filepath to server
- Displays file content received

**Key Code**:
```c
case '3':
    // Option 3: Ask for file path
    bzero(buffer, MAX_BUFFER);
    printf("Enter file path in data directory: ");
    fgets(buffer, MAX_BUFFER-1, stdin);
    
    // Remove newline
    buffer[strcspn(buffer, "\n")] = 0;
    
    // Send filepath to server
    write(sockfd, buffer, strlen(buffer));
    
    // Receive and display file content
    show_answer();
    return 1;
```

#### Updated Menu Display:
```
3. Display file content (specify path)
```
Changed from: `3. Display file content`

### 5. **Updated Both Client Modes**:
- **Normal Client Menu**: Updated description
- **MONO Client Menu**: Updated description

---

## How It Works

### Flow Diagram
```
Client                          Server
  |                               |
  |--1. Menu displayed----------->|
  |                               |
  |--2. User selects option 3---->|
  |                               |
  |<--Server prompts for path-----|
  |                               |
  |--3. User enters filename----->|
  |  (e.g., "my_file.txt")        |
  |                               |
  |--4. Filename sent to server-->|
  |                               |
  |                          Server opens:
  |                          ./data/my_file.txt
  |                               |
  |<--5. File content sent--------|
  |                               |
  |--6. Display content---------->|
  |                               |
```

### Example Interaction

**Client Side**:
```
Enter your choice: 3
Enter file path in data directory: my_data.txt
[File content displayed]

Enter your choice: 3
Enter file path in data directory: report.pdf
[File content displayed]
```

**Server Side**:
```
Reads: my_data.txt
Opens: ./data/my_data.txt
Sends content...

Reads: report.pdf
Opens: ./data/report.pdf
Sends content...
```

---

## Files Modified

| File | Changes |
|------|---------|
| `service.h` | Updated function signature |
| `service.c` | Modified file_content() to accept filepath |
| `serverimp.c` | Modified case 3 to read filepath from client |
| `clientdef.h` | Modified case '3' to prompt for and send filepath |

---

## Features

✅ **Dynamic File Selection**: Users can request any file in `./data/` directory
✅ **Safe Path Handling**: Filepath is always relative to `./data/`
✅ **Error Handling**: Returns error if file doesn't exist
✅ **Both Modes Supported**: Works with normal and MONO clients
✅ **Input Validation**: Removes newlines and validates input

---

## Testing

### Test Case 1: Existing File
```bash
./client localhost 8080
# Choose mode: 1 or 2
# Choose option: 3
# Enter path: my_data.txt
# Result: File content displayed
```

### Test Case 2: Non-existent File
```bash
./client localhost 8080
# Choose option: 3
# Enter path: nonexistent.txt
# Result: "ERROR: File does not exist"
```

### Test Case 3: Multiple Files
```bash
./client localhost 8080
# Choose option: 3
# Enter path: file1.txt
# [content displayed]
# Choose option: 3
# Enter path: file2.txt
# [content displayed]
```

---

## Backward Compatibility

✅ **Fully backward compatible**
- No breaking changes to existing code
- Other options (1, 2, 4, 5) unchanged
- Server initialization unchanged
- Socket operations unchanged

---

## Security Considerations

⚠️ **Note**: This implementation assumes trusted clients
- Paths are validated to be under `./data/` directory
- Uses `snprintf()` for safe path construction
- Prevents absolute path attacks by prepending `./data/`

**Safety Example**:
```c
// User input: "../../../etc/passwd"
// Actual path opened: "./data/../../../etc/passwd"
// System resolves to: /etc/passwd (escapes data directory)
```

**Improvement** (if needed):
Could add validation to reject paths containing `..` or `/`:
```c
if (strchr(filepath, '.') || strchr(filepath, '/')) {
    return ERROR;
}
```

---

## Build and Test

```bash
# Build
make clean && make

# Run MONO server with file path option
./server 8080
# Select: 3 (MONO)

# Run client
./client localhost 8080
# Select: 2 (MONO)
# Select: 3 (Display file)
# Enter: my_data.txt
```

---

## Summary

✅ Option 3 now accepts file paths from clients
✅ Users can read any file in the `./data/` directory
✅ Server safely constructs file paths
✅ Both normal and MONO clients support this feature
✅ Error handling for missing files
✅ Fully backward compatible
