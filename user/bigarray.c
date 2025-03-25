#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define N 65536 // 2^16
#define NUM_CHILDREN 4
int
main(int argc, char *argv[])
{
    int *array = malloc(N * sizeof(int));
    if(!array) {
        printf("malloc failed\n");
        exit(1);
    }
    int pids[NUM_CHILDREN];
    int n_finished;
    int statuses[64];
    int total = 0;

    for (int i = 0; i < N; i++) {
        array[i] = i;
    }
    
    int proc_num = forkn(NUM_CHILDREN, pids);
    if (proc_num < 0) {
        free(array);
        printf("forkn failed\n");
        exit(1);
    }

    if(proc_num > 0) {
        // Calculate the child's portion
        int portion = N / NUM_CHILDREN;
        int start = portion * (proc_num - 1);
        int end = start + portion;
        int sum = 0;

        // Sum this portion
        for(int i = start; i < end; i++) {
            sum += array[i];
        }
        free(array);
        printf("Child %d, Sum = %d\n", proc_num, sum);
        exit(sum);
    }
    else {
        // Wait for all children to finish
        if(waitall(&n_finished, statuses) < 0) {
            free(array);
            printf("waitall failed\n");
            exit(1);
        }

        // Sum all the children's sums
        for(int i = 0; i < n_finished; i++) {
            //printf("Child %d exited with sum %d\n", i + 1, statuses[i]);
            total += statuses[i];
        }
        free(array);
        printf("Total Sum = %d\n", total);
        exit(0);
    }

}