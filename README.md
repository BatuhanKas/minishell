# 🐚 MiniShell

**École 42 Minishell Project** - A simple Unix shell implementation that mimics the basic features of Bash.

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [Built-in Commands](#-built-in-commands)
- [Technical Details](#-technical-details)
- [Project Structure](#-project-structure)
- [Examples](#-examples)

## 🎯 Overview

MiniShell is a Unix shell application developed as part of the École 42 curriculum. This project aims to develop a deep understanding of system programming, process management, file descriptors, and parsing.

The project allows users to execute system commands through a command-line interface, use pipes and redirections, and manage environment variables.

## ✨ Features

### Command Execution
- ✅ Finding and executing commands from PATH
- ✅ Relative and absolute path support
- ✅ Command argument handling

### Redirections
- ✅ `<` - Input redirection
- ✅ `>` - Output redirection (overwrite)
- ✅ `>>` - Output redirection (append)
- ✅ `<<` - Heredoc (read input until delimiter)

### Pipe Operations
- ✅ Pipe (`|`) support between multiple commands
- ✅ Unlimited pipe chains
- ✅ File descriptor management between pipes

### Quotes and Special Characters
- ✅ Single quotes (`'`) - Ignore all metacharacters
- ✅ Double quotes (`"`) - Ignore metacharacters except $
- ✅ Escape character (`\`) support

### Environment Variables
- ✅ `$VAR` - Variable expansion
- ✅ `$?` - Exit status of last command
- ✅ Variable expansion within double quotes

### Signal Management
- ✅ `Ctrl-C` - SIGINT (terminate current command)
- ✅ `Ctrl-D` - EOF (exit shell)
- ✅ `Ctrl-\` - SIGQUIT (do nothing)

## 🔧 Installation

### Requirements

- GCC compiler
- GNU Make
- readline library

```bash
# Install readline on macOS
brew install readline

# Install readline on Linux
sudo apt-get install libreadline-dev
```

### Compilation

```bash
# Clone the repository
git clone [repository-url] minishell
cd minishell

# Compile
make

# Clean
make clean      # Remove object files
make fclean     # Remove all compiled files
make re         # Recompile
```

## 🚀 Usage

```bash
# Start MiniShell
./minishell

# Shell is running
MiniShell$ echo "Hello World"
MiniShell$ ls -la | grep minishell
MiniShell$ cat < input.txt > output.txt
MiniShell$ export MY_VAR=42
MiniShell$ echo $MY_VAR
```

## 📦 Built-in Commands

### `echo`
Prints text to the screen. The `-n` flag suppresses the newline character.
```bash
echo Hello World
echo -n "No newline"
```

### `cd`
Changes the current working directory.
```bash
cd /path/to/directory
cd ..
cd ~
cd        # Goes to HOME directory
```

### `pwd`
Prints the current working directory.
```bash
pwd
```

### `export`
Creates or updates environment variables.
```bash
export VAR=value
export PATH=/usr/bin:$PATH
export          # List all exported variables
```

### `unset`
Removes environment variables.
```bash
unset VAR
```

### `env`
Lists all environment variables.
```bash
env
```

### `exit`
Exits the shell. Optional exit code can be specified.
```bash
exit
exit 42
```

## 🛠 Technical Details

### Memory Management
- All dynamic memory allocations are properly freed
- Valgrind can be used for memory leak checking
- Temporary memory cleanup after each command

### Process Management
- Creating child processes with `fork()`
- Executing commands with `execve()`
- Process tracking with `waitpid()`
- Process synchronization for pipes

### Parsing
- Tokenization and lexical analysis
- Parsing within and outside quotes
- Special character handling
- Syntax error checking

### Error Management
- Appropriate messages for syntax errors
- Command not found (127)
- Permission denied errors
- Exit status codes

## 📁 Project Structure

```
minishell/
├── main.c                      # Main program loop and signal management
├── Makefile                    # Compilation configuration
├── include/
│   └── minishell.h            # Header file and struct definitions
├── built-in/                   # Built-in commands
│   ├── built-in.c             # Built-in dispatcher
│   ├── cd.c                   # cd command
│   ├── echo.c                 # echo command
│   ├── env.c                  # env command
│   ├── exit.c                 # exit command
│   ├── export.c               # export command
│   ├── pwd.c                  # pwd command
│   └── unset.c                # unset command
├── execute/                    # Command execution
│   ├── add_pipes.c            # Pipe structure creation
│   ├── execute_command.c      # Command execution
│   ├── next_process.c         # Pipe chain management
│   └── redir_execute.c        # Redirection execution
├── init_and_find_path/         # Initialization and PATH
│   ├── find_env.c             # Environment variable lookup
│   ├── find_path.c            # Command search in PATH
│   └── ms_init.c              # Shell initialization
├── redirections/               # Redirection operations
│   ├── redir_heredoc.c        # Heredoc processing
│   ├── redir_order.c          # Redirection ordering
│   ├── redir_run.c            # Redirection execution
│   └── redir_set.c            # Redirection setup
├── syntax/                     # Parsing and syntax
│   ├── add_cmd.c              # Command token processing
│   ├── dollar_parse.c         # Variable expansion
│   └── quate_parse.c          # Quote handling
└── libft/                      # Utility function library
    ├── ft_split.c
    ├── ft_strjoin.c
    └── ... (other utility functions)
```

## 💡 Examples

### Simple Commands
```bash
MiniShell$ ls -la
MiniShell$ cat file.txt
MiniShell$ grep "pattern" file.txt
```

### Using Pipes
```bash
MiniShell$ ls -la | grep minishell | wc -l
MiniShell$ cat file.txt | grep "error" | sort | uniq
```

### Redirections
```bash
MiniShell$ echo "Hello" > output.txt
MiniShell$ cat < input.txt > output.txt
MiniShell$ ls -la >> log.txt
```

### Heredoc
```bash
MiniShell$ cat << EOF
> Line 1
> Line 2
> EOF
```

### Environment Variables
```bash
MiniShell$ export NAME="John"
MiniShell$ echo "Hello $NAME"
MiniShell$ echo "Exit code: $?"
```

### Using Quotes
```bash
MiniShell$ echo 'Single quotes: $USER'
MiniShell$ echo "Double quotes: $USER"
MiniShell$ echo "Mixed 'quotes' work"
```

### Complex Combinations
```bash
MiniShell$ < input.txt grep "error" | sort | uniq > output.txt
MiniShell$ export PATH=/bin:/usr/bin && ls | wc -l
```

## 🎓 Learning Outcomes

Throughout this project, in-depth knowledge was gained in the following topics:

- **System Programming**: Fork, exec, wait system calls
- **Process Management**: Creating and managing child processes
- **Pipes and IPC**: Inter-process communication
- **File Descriptors**: FD management with dup2, close
- **Signal Handling**: SIGINT, SIGQUIT management
- **Parsing**: Lexical analysis and tokenization
- **Memory Management**: Malloc, free and leak prevention
- **UNIX Shell**: Understanding Bash behavior

## ⚠️ Known Limitations

- Wildcard (*) expansion is not supported
- History navigation (up/down arrows) is limited
- Job control (bg, fg, jobs) is not supported
- Subshells (parentheses usage) are not supported
- Logical operators (&&, ||) are not supported

## 📝 License

This project is part of the École 42 curriculum and was developed for educational purposes.

## 👥 Contributors

- **bkas** - Developer
- **melihyil** - Developer

---

**École 42** | Minishell Projesi | 2024
