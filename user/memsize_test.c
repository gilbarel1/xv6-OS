#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define KB 1024

int main(int argc, char *argv[]) {
    printf("memsize: %d\n", memsize());
    int *p = malloc(20000);
    printf("memsize: %d\n", memsize());
    free(p);
    printf("memsize: %d\n", memsize());
    exit(0, "memsize_test complete");
}