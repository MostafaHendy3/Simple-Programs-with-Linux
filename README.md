# Simple-Programs-with-Linux

- Proram One : Simple Shell
    - Wish Shell

A simple shell implementation in C.
Usage

```
./wish [batch.txt]
```
Features

    Execute commands from the command line
    Supports batch mode by reading commands from a file
    Implements the exit command to exit the shell

Building

To build the wish shell, simply compile the wish.c file using a C compiler:

```
gcc wish.c -o wish
```
Running

To run the wish shell, execute the compiled binary:

```
 ./wish
```
You will be presented with a prompt Wish>. Enter a command to execute it.
Batch Mode

To run the wish shell in batch mode, provide a file containing commands as an argument:

```
 ./wish batch.txt
```
The shell will read and execute the commands from the file.

