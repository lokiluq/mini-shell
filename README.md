# mini-shell

✅ Features

🖥️ Prompt & Execution
Interactive Prompt: Displays a shell prompt while waiting for user input.

Command Execution: Parses and executes built-in and external commands.

PATH Resolution: Searches executables using PATH or direct paths.

Single Global Variable: Uses only one global variable throughout the program.

📝 Command History
History Support: Maintains a working history of executed commands.

🔠 Quoting Rules
Single Quotes ': Preserve literal value of characters (no interpretation).

Double Quotes ": Preserve literal value, except for $ (used for variable expansion).

🔁 Redirections
<   : Redirects input from a file.

>   : Redirects output to a file (overwrite).

>>  : Redirects output in append mode.

<<  : "Here-document" — reads input until a delimiter line is encountered.

🔗 Pipes
Supports pipelines (|), passing the output of one command as input to the next.

🌍 Environment Variables
Expands environment variables using $.

Special variable $? holds the exit status of the last executed pipeline.

🚦 Signal Handling
Ctrl+C : Interrupts current input and displays a new prompt.

Ctrl+D : Exits the shell.

Ctrl+\ : Ignored (no action).

🛠 Built-in Commands
echo [-n]    : Prints text to standard output.

cd [dir]     : Changes the current working directory.

pwd       : Prints the current working directory.

export [VAR=VAL]: Adds or modifies environment variables.

unset [VAR]  : Removes environment variables.

env       : Displays the current environment.

exit       : Exits the shell.

🚫 Special Character Handling
Does not interpret unclosed quotes or non-essential characters like \ or ;.
