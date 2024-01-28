# Minishell - 42 School Project

## Description
Minishell is a simplified shell program developed as part of the 42 school curriculum. It is designed to understand and execute basic shell commands, handle environment variables, and manage processes.

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Command Examples](#command-examples)
- [Built-in Commands](#built-in-commands)
- [Bonus](#bonus)
- [Testing](#testing)

## Features
- Command execution
- Redirection and pipes
- Environment variable support
- Signal handling
- Basic error handling

## Getting Started

### Prerequisites
- GCC compiler
- Make
- [libft](https://github.com/Vaache/libft) (your personal library or the school's standard library)

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/Vaache/minishell.git
   cd minishell
   ```
2. Build the project:
	```bash
	make readline; make
   ```
### Usage:
1. Run the Minishell executable:
   ```bash
	./minishell

### Built-in Commands
Minishell supports the following built-in commands:

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`


### Bonus
Additional Features
Job Control: Implement job control features like fg, bg, and jobs.
Command Line Editing: Add line editing capabilities with features like history, arrow key navigation, and editing.
Tab Completion: Support tab completion for commands and file paths.
### Logical Operators
- **&& and ||:** Implement the logical operators `&&` and `||` to allow chaining of commands based on the success or failure of previous commands.

```bash
command1 && command2  # Execute command2 only if command1 succeeds
command1 || command2  # Execute command2 only if command1 fails
```

### Command Grouping
Command Grouping with (): Allow command grouping using parentheses to change the precedence of execution.
	```bash
	(command1 && command2) || command3
	```

### Testing
Include comprehensive test cases to ensure the correctness and robustness of your shell.
Use a test suite or framework to automate testing.
Performance Optimization
Optimize the performance of your shell, especially for handling large inputs and executing complex commands.
This section suggests the addition of logical operators && and || for command chaining based on success or failure and the use of parentheses for command grouping to change the precedence of execution. Feel free to further customize or expand this section based on specific implementation details or additional features you've included in your Minishell project.
