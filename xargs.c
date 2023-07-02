#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


int main(int argc, char*argv[])
{
    int n;
    char buf[100];
    char *command;
    char *line;
    char args[100];
    int arg_idx;

    if (argc < 2)
    {
        printf("Wrong format!\n");
        exit(0);
    }

    command = argv[1];

    while ((line = gets(buf, sizeof(buf))))
    {
        arg_idx = 0;
        args[arg_idx++] = *command;

        char *token = strtok(line, " ");
        while (token)
        {
            args[arg_idx++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_idx] = 0;

        int pid = fork();
        if (pid < 0)
        {
            fprintf(2, "创建子进程失败\n");
            exit(0);
        }
        else if (pid == 0)
        {
            exec(args[0], args);
            fprintf(2, "执行命令失败\n");
            exit(0);
        }
        else
        {
            sleep(10);
        }
    }
}
