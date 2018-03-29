#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct arg_t
{
    int order;
    int label;
};

int L(int num)
{
    if (num == 0 | num == 1) //base case: L(0) & l(1) always equal 1
        return 1;
    else
        return L(num - 1) + L(num - 2) + 1;
}

void *thread_routine(void *args)
{
    struct arg_t *arg = args;
    if (arg->order == 0 || arg->order == 1)
    {
        //case for leaf node; no left or right threads made

        printf("[%d]\n", arg->label); //print label
        return NULL;
    }

    printf("(%d\n", arg->label);

    pthread_t left_child_tid;
    struct arg_t *left_child_arg = (struct arg_t*)malloc(sizeof (struct arg_t));
    left_child_arg->order = arg->order - 1;
    left_child_arg->label = arg->label + 1;
    pthread_create(&left_child_tid, NULL, thread_routine, left_child_arg);

    pthread_t right_child_tid;
    struct arg_t *right_child_arg = (struct arg_t*)malloc(sizeof (struct arg_t));
    right_child_arg->order = arg->order - 2;
    right_child_arg->label = arg->label + 1 + L(arg->order - 1);
    pthread_create(&right_child_tid, NULL, thread_routine, right_child_arg);

    pthread_join(left_child_tid, NULL);
    pthread_join(right_child_tid, NULL);

    free(left_child_arg);
    free(right_child_arg);

    printf("%d)\n", arg->label);
    return NULL;
}

void leothread(int N)
{
    struct arg_t *firstarg = (struct arg_t*)malloc(sizeof (struct arg_t));
    firstarg->order = N;
    firstarg->label = 0;
    thread_routine(firstarg);
    return;
}

int main()
{
    leothread(4);
    return 0;
}
