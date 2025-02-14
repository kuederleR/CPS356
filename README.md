# Pipe WC Programs

## Overview

This project contains two programs that create a pipe and fork a child process to execute the `wc` command. The parent process reads from a file and writes its contents to the pipe. The child process reads from the pipe and passes the data to `wc` to count lines, words, and characters.

## Files

- `pipe_wc_linux.c`: Implementation for Linux.
- `pipe_wc_xv6.c`: Implementation for xv6.

## How to Execute

### Linux

1. Compile the program:
    ```sh
    gcc -o pipe_wc_linux pipe_wc_linux.c
    ```

2. Run the program:
    ```sh
    ./pipe_wc_linux <filename>
    ```

### xv6

1. Copy `pipe_wc_xv6.c` to the xv6 source directory.
2. Add the program to the `Makefile` in the xv6 source directory.
3. Rebuild xv6:
    ```sh
    make qemu
    ```

4. Run the program inside xv6:
    ```sh
    pipe_wc_xv6 <filename>
    ```
