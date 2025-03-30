#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Дочерний процесс
        printf("Child:  PID=%d, PPID=%d\n", getpid(), getppid());
        // Длительные вычисления (цикл)
        for (int i = 0; i < 5; i++) {
            printf("Child progress: %d/5\n", i + 1);
            volatile long j; // volatile для избежания оптимизации
            for (j = 0; j < 100000000L; j++);
        }
    } else {
        // Родительский процесс
        printf("Parent: PID=%d, PPID=%d\n", getpid(), getppid());
        // Длительные вычисления (цикл)
        for (int i = 0; i < 5; i++) {
            printf("Parent progress: %d/5\n", i + 1);
            volatile long j;
            for (j = 0; j < 100000000L; j++);
        }
        wait(NULL); // Ожидание завершения потомка
    }

    printf("Process %d finished\n", getpid());
    return 0;
}
