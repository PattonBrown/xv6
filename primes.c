#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define MAX_NUM 35
#define READ_END 0
#define WRITE_END 1

void sieve(int);
void prime_numbers();

int main()
{
    int pipe_fd[2];
    pipe(pipe_fd);

    if (fork() == 0) {
        close(pipe_fd[WRITE_END]);
        sieve(pipe_fd[READ_END]);
    } else {
        close(pipe_fd[READ_END]);

        for (int i = 2; i <= MAX_NUM; i++) {
            write(pipe_fd[WRITE_END], &i, sizeof(int));
        }

        close(pipe_fd[WRITE_END]);

        wait(0);
    }

    exit(0);
}

void sieve(int read_fd)
{
    int pipe_fd[2];
    pipe(pipe_fd);

    int prime;
    if (read(read_fd, &prime, sizeof(int)) == 0) {
        exit(0);
    }

    printf("prime %d\n", prime);

    if (fork() == 0) {
        close(pipe_fd[WRITE_END]);
        sieve(pipe_fd[READ_END]);
    } else {
        close(pipe_fd[READ_END]);

        int num;
        while (read(read_fd, &num, sizeof(int))) {
            if (num % prime != 0) {
                write(pipe_fd[WRITE_END], &num, sizeof(int));
            }
        }

        close(read_fd);
        close(pipe_fd[WRITE_END]);

        wait(0);
        exit(0);
    }
}
