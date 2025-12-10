# Getting Started with TCP Client-Server

## Repository Status

✅ **Repository Created**: tcp_cl_sr(working)
✅ **Initial Files Pushed**: README.md, server.c, client.c, .gitignore
⏳ **Remaining Files**: To be pushed via local git from WSL

## How to Set Up Locally

### Clone the Repository

```bash
git clone https://github.com/thamer-elhani/tcp_cl_sr-working-.git
cd tcp_cl_sr-working-
```

### Copy Files from Local Version

The remaining source files need to be copied from your local version3 folder:

```bash
# From your local machine
cp /home/thamer/tcp_cl_sr/version2/version3/*.c .
cp /home/thamer/tcp_cl_sr/version2/version3/*.h .
cp /home/thamer/tcp_cl_sr/version2/version3/Makefile .
cp -r /home/thamer/tcp_cl_sr/version2/version3/data .
```

### Build the Project

```bash
make clean && make
```

### Verify Build

```bash
ls -la server client
```

Both executables should exist and be executable.

## Required Source Files

The following source files are needed (already in your local version3):

```
server.c              - Main server (✅ PUSHED)
client.c              - Main client (✅ PUSHED)
serverimp.c           - Server implementation (needed)
clientdef.h           - Client functions (needed)
serverdef.h           - Server header (needed)
service.c             - Service functions (needed)
service.h             - Service header (needed)
Makefile              - Build configuration (needed)
data/my_data.txt      - Sample data file (needed)
```

## Complete Push Instructions

Once you have the repository cloned locally, you can push all remaining files:

```bash
# From the cloned repository directory

# Copy remaining files
cp /home/thamer/tcp_cl_sr/version2/version3/serverimp.c .
cp /home/thamer/tcp_cl_sr/version2/version3/clientdef.h .
cp /home/thamer/tcp_cl_sr/version2/version3/serverdef.h .
cp /home/thamer/tcp_cl_sr/version2/version3/service.c .
cp /home/thamer/tcp_cl_sr/version2/version3/service.h .
cp /home/thamer/tcp_cl_sr/version2/version3/Makefile .
mkdir -p data
cp /home/thamer/tcp_cl_sr/version2/version3/data/my_data.txt data/

# Create authentication token
# Visit: https://github.com/settings/tokens
# Create token with 'repo' scope
# Then use:
git config --global user.email "your-email@example.com"
git config --global user.name "Your Name"

# Configure credential helper for authentication
git config --global credential.helper store

# Push changes
git add .
git commit -m "Add all source files and build configuration"
git push origin main

# Enter GitHub token when prompted (use token as password)
```

## Alternative: SSH Setup

If you prefer SSH authentication:

```bash
# Generate SSH key (if not already done)
ssh-keygen -t ed25519 -C "your-email@example.com"

# Add to GitHub SSH keys
cat ~/.ssh/id_ed25519.pub
# Paste at: https://github.com/settings/ssh/new

# Configure SSH
git config --global url."git@github.com:".insteadOf "https://github.com/"

# Now push
git push origin main
```

## Documentation

All documentation files from version3 can also be pushed:

```bash
cp /home/thamer/tcp_cl_sr/version2/version3/*.md .
git add *.md
git commit -m "Add comprehensive documentation"
git push origin main
```

## Verify Repository

Once pushed, verify at:
```
https://github.com/thamer-elhani/tcp_cl_sr-working-/
```

## Quick Start After Clone

```bash
# Clone
git clone https://github.com/thamer-elhani/tcp_cl_sr-working-.git
cd tcp_cl_sr-working-

# Copy files (from local version3)
for file in serverimp.c clientdef.h serverdef.h service.c service.h Makefile; do
  cp /home/thamer/tcp_cl_sr/version2/version3/$file .
done
cp -r /home/thamer/tcp_cl_sr/version2/version3/data .

# Build
make clean && make

# Test MONO server
./server 8080 &
SERVER_PID=$!
sleep 1

# Test MONO client
echo "2
3
my_data.txt
" | ./client localhost 8080

# Cleanup
kill $SERVER_PID

# If successful, push to GitHub
git add .
git commit -m "Add remaining source files"
git push origin main
```

## Troubleshooting

### Git Authentication Error

```bash
# Clear cached credentials
git config --global --unset credential.helper
git credential reject

# Reconfigure with token
git config --global credential.helper store
```

### Permission Denied (SSH)

```bash
# Check SSH key permissions
chmod 600 ~/.ssh/id_ed25519
chmod 700 ~/.ssh

# Verify key is added to agent
ssh-add ~/.ssh/id_ed25519
```

### File Not Found

Ensure you're in the cloned repository directory:

```bash
pwd
# Should show: .../tcp_cl_sr-working-

ls -la server.c client.c
# Both should exist
```

## Support

For questions or issues with pushing files to GitHub, please refer to:
- GitHub Documentation: https://docs.github.com/en/github
- Git Documentation: https://git-scm.com/doc

---

**Status**: Repository initialized and ready for local file synchronization
