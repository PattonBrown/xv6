#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
    int index=0,argIndex = 0;
    int bytesRead,blockIndex;
    int bufIndex= 0;
    char buffer[100];
    char buffer2[100];
    char *argPtr = buffer2;
    char *lines[100];

    for (index = 1; index < argc; index++)
    {
        lines[argIndex++] = argv[index];
    }
    while ((bytesRead = read(0, buffer, sizeof(buffer))) > 0)
    {
        for (blockIndex = 0; blockIndex < bytesRead; blockIndex++)
        {
            if (buffer[blockIndex] == '\n')
            {
                // 将当前缓冲区的内容结束标志符置为0
                buffer2[bufIndex] = 0;
                bufIndex = 0;

                // 将当前行的指针添加到 lines 数组中
                lines[argIndex++] = argPtr;
                argPtr = buffer2;

                // 在 lines 数组最后添加NULL作为参数结束标志
                lines[argIndex] = 0;

                // 将命令的执行参数和当前行的参数合并为一个参数数组
                argIndex = argc - 1;

                // 创建子进程执行命令
                if (fork() == 0)
                {
                    // 在子进程中通过 exec 执行命令
                    exec(argv[1], lines);
                }
                // 父进程等待子进程完成
                wait(0);
            }
            // 如果遇到空格符，则表示一个参数结束
            else if (buffer[blockIndex] == ' ')
            {
                // 将当前缓冲区的内容结束标志符置为0
                buffer2[bufIndex++] = 0;

                // 将当前参数的指针添加到 lines 数组中
                lines[argIndex++] = argPtr;
                argPtr = &buffer2[bufIndex];
            }
            // 其他情况下，将字符添加到当前缓冲区
            else
            {
                buffer2[bufIndex++] = buffer[blockIndex];
            }
        }
    }
    exit(0);
}
