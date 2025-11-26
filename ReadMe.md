Simple Windows Shell Tutorial

This project is a tutorial implementation of a simple shell in C on Windows.

⚠️ Note: This is not a production shell. The goal of this project is learning and understanding how a shell works internally, including reading user input, parsing commands, handling built-in commands, and executing external programs using CreateProcess().

Features

Read user input

Uses ish_read_line() to read a full command line from the user.

Parse commands

lsh_split_line() splits the input into command and arguments.

Built-in commands

Supports simple built-ins like:

cd → just prints "cd command" (for tutorial purposes)

help → lists available commands

exit → exits the shell loop

External commands

Any other command is executed as a separate process using Windows CreateProcess().

The parent shell waits for the child process to finish before accepting the next command.

Loop

The shell continuously prompts the user until exit is entered.

How It Works (Tutorial Purpose)

User input → read with getchar()

Parse input → split into array of arguments

Check built-ins → execute internally if found

External command → run using CreateProcess() as a new process

Wait for process → parent waits for child to finish

Repeat loop → back to step 1

This implementation is designed to help understand how a shell works, not to be used as a production shell.

Example

Enter command line:

help

Available commands: cd, help, exit

Enter command line:

notepad

// Opens Notepad in a separate process.

Requirements

Windows OS

C compiler supporting Windows API (e.g., MinGW, Visual Studio, CLion)

License

This project is for learning and tutorial purposes only.

This project follows (and simplifies) the excellent tutorial:

“Write a Shell in C” by Stephen Brennan

 https://brennan.io/2015/01/16/write-a-shell-in-c/