#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    int p1[2], p2[2];
    char buf[1];
    pipe(p1);
    pipe(p2);
    if (fork() == 0) {
        if (read(p1[0], buf, 1)) {
            fprintf(1, "%d: received ping\n", getpid());
        }
        write(p2[1], buf, 1);
        close(p2[1]);
    } else {
        write(p1[1], "A", 1);
        if (read(p2[0], buf, 1)) {
            fprintf(1, "%d: received pong\n", getpid());
        }
        close(p1[1]);
    }

   exit(0);
}
