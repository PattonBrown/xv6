#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int primesFigure(int n)
{
    for (int i = 2; i*i <= n ; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int n, pid;
    int fds[2];
    char buf[20];

    pipe(fds);

    pid = fork();
    if (pid == 0)
    {
        // fprintf(1,"%d\n",getpid());
        for (int i = 2; i <= 35; i++)
        {
            if (primesFigure(i) == 1)
            {
                fprintf(1,"prime %d\n",i);
                write(fds[1], buf, sizeof(buf));
            }
        }
    }
    else
    {
        n = read(fds[0], buf, sizeof(buf));
        write(1, buf, n);
        sleep(10);
    }
    exit(0);
}
