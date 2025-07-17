# mini-shell

# 🐚 Minishell

A simplified custom shell implementation built in C.  
This project recreates essential features of a Unix shell such as command parsing, execution, redirection, piping, and signal handling — all from scratch.

---

## ✅ Features

### 🖥️ Prompt & Execution
- **Interactive Prompt**: Displays a shell prompt while waiting for user input.
- **Command Execution**: Parses and executes built-in and external commands.
- **PATH Resolution**: Searches executables using `PATH` or direct paths.
- **Single Global Variable**: Uses only one global variable throughout the program.

### 📝 Command History
- **History Support**: Maintains a working history of executed commands.

### 🔠 Quoting Rules
- **Single Quotes `'`**: Preserve literal value of characters (no interpretation).
- **Double Quotes `"`**: Preserve literal value, except for `$` (used for variable expansion).

### 🔁 Redirections
- `<`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Redirects input from a file.  
- `>`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Redirects output to a file (overwrite).  
- `>>`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Redirects output in append mode.  
- `<<`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Here-document — reads input until a delimiter is encountered.

### 🔗 Pipes
- **Pipelines**: Connects multiple commands using `|`, where the output of one becomes the input of the next.

### 🌍 Environment Variables
- **Expansion with `$`**: Expands environment variables.
- **Exit Status `$?`**: Represents the exit status of the last executed pipeline.

### 🚦 Signal Handling
- `Ctrl + C`&nbsp;&nbsp;&nbsp;&nbsp;: Interrupts current input and shows a fresh prompt.  
- `Ctrl + D`&nbsp;&nbsp;&nbsp;&nbsp;: Exits the shell.  
- `Ctrl + \`&nbsp;&nbsp;&nbsp;&nbsp;: Ignored (no action taken).

### 🛠 Built-in Commands
- `echo [-n]`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Prints text to standard output.  
- `cd [dir]`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Changes current working directory.  
- `pwd`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Prints current working directory.  
- `export [VAR=VAL]`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Adds or modifies environment variables.  
- `unset [VAR]`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Removes environment variables.  
- `env`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Displays environment variables.  
- `exit`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Exits the shell.

### 🚫 Special Character Handling
- Unclosed quotes or non-essential special characters (e.g. `\`, `;`) are **not** interpreted.

---

## 🧠 Purpose

This project is a deep dive into how Unix shells work under the hood. It strengthens your grasp of:
- Process control (`fork`, `execve`, `wait`)
- File descriptors and redirection
- Signal handling
- Parsing logic and command execution flow

---


