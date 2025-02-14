#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf(2, "open: cannot open %s\n", argv[1]);
        exit();
    }

    int p[2];
    pipe(p);

    if (fork() == 0) {
        // Child process: set up pipe so that wc reads from it.
        close(p[1]);  // Close write end
        dup(p[0], 0);
        close(p[0]);
        execl("wc", "wc", 0);
        printf(2, "execl: failed to execute wc\n");
        exit();
    } else {
        // Parent process: read file and write its contents into the pipe.
        close(p[0]);  // Close read end
        char buf[BUF_SIZE];
        int n;
        while ((n = read(fd, buf, sizeof(buf))) > 0) {
            write(p[1], buf, n);
        }
        close(p[1]); // Close write end to signal EOF
        close(fd);
        wait();
    }
    exit();
}
