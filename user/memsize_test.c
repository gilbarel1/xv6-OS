#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define KB 1024

int main(int argc, char *argv[]) {
    printf("memsize: %d\n", memsize());
    char *p = malloc(20000);
    printf("memsize after malloc: %d\n", memsize());
    free(p);
    printf("memsize after release: %d\n", memsize());
    exit(0);
}