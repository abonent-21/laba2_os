#define _GNU_SOURCE  // Важно: должно быть в самом начале
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

// Функция для потоков, созданных через pthread_create()
void *thread_func(void *arg) {
    int id = *(int *)arg;
    printf("Pthread thread %d started (PID: %d, TID: %lu)\n", 
           id, getpid(), (unsigned long)pthread_self());
    sleep(1);
    printf("Pthread thread %d exiting\n", id);
    return NULL;
}

// Функция для потока, созданного через clone()
int clone_func(void *arg) {
    int id = *(int *)arg;
    printf("Clone thread %d started (PID: %d)\n", id, getpid());
    sleep(1);
    printf("Clone thread %d exiting\n", id);
    return 0;
}

int main() {
    pthread_t tid1, tid2;
    int arg1 = 1, arg2 = 2;

    // Создание потоков через pthread_create()
    pthread_create(&tid1, NULL, thread_func, &arg1);
    pthread_create(&tid2, NULL, thread_func, &arg2);

    // Создание потока через clone()
    int arg_clone = 3;
    const size_t stack_size = 4096;
    void *stack = malloc(stack_size);
    if (!stack) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    void *stack_top = (char *)stack + stack_size;

    // Флаги: CLONE_VM (общая память) и SIGCHLD (для ожидания через waitpid)
    int flags = CLONE_VM | SIGCHLD;
    pid_t cpid = clone(clone_func, stack_top, flags, &arg_clone);
    if (cpid == -1) {
        perror("clone");
        free(stack);
        exit(EXIT_FAILURE);
    }

    // Ожидание завершения pthread-потоков
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Ожидание завершения clone-потока
    waitpid(cpid, NULL, 0);
    free(stack);

    printf("All threads have exited\n");
    return 0;
}
