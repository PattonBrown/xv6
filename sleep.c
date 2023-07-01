#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(1, "usage: sleep time...\n");
        exit(-1);
    }
    sleep(atoi(argv[1]));
    fprintf(1, "(nothing happens for a little while)\n");
    exit(0);
}
