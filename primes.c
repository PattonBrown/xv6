#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int primesFigure(int n)
{
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % 2 == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int n, pid;
    int fds[2];
    char buf[100];

    pipe(fds);

    pid = fork();
    if (pid == 0)
    {
        // fprintf(1,"%d\n",getpid());
        for (int i = 2; i <= 35; i++)
        {
            if (primesFigure(i) == 1)
            {
                write(fds[1], i, sizeof(i));
            }
        }
    }
    else
    {
        n = read(fds[0], buf, sizeof(buf));
        write(1, buf, n);
    }
    exit(0);
}
