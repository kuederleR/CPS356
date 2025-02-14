#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    int p[2];
    pipe(p);

    if (fork() == 0) {
        // Child process: set up pipe so that wc reads from it.
        close(p[1]);  // Close write end
        dup2(p[0], STDIN_FILENO);
        close(p[0]);
        execlp("wc", "wc", (char *)NULL);
        perror("execlp");
        exit(1);
    } else {
        // Parent process: read file and write its contents into the pipe.
        close(p[0]);  // Close read end
        char buf[BUF_SIZE];
        ssize_t n;
        // Read from file and write to pipe
        while ((n = read(fd, buf, BUF_SIZE)) > 0) {
            write(p[1], buf, n);
        }
        close(p[1]); // Close write end to signal EOF
        close(fd);
        wait(NULL); // Wait for child to finish
    }
    return 0;
}
