#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t child1, child2, child3;
    int status;

    // Создание трех дочерних процессов
    child1 = fork();
    if (child1 == 0) {
        printf("Child1 (PID=%d) started\n", getpid());
        sleep(3);
        printf("Child1 exiting\n");
        exit(10);
    }

    child2 = fork();
    if (child2 == 0) {
        printf("Child2 (PID=%d) started\n", getpid());
        sleep(5);
        printf("Child2 exiting\n");
        exit(20);
    }

    child3 = fork();
    if (child3 == 0) {
        printf("Child3 (PID=%d) started\n", getpid());
        sleep(1);
        printf("Child3 exiting\n");
        exit(30);
    }

    // Родитель ожидает завершения child2
    printf("Parent (PID=%d) waiting for child2 (PID=%d)...\n", getpid(), child2);
    waitpid(child2, &status, 0);

    if (WIFEXITED(status)) {
        printf("Child2 exited with status: %d\n", WEXITSTATUS(status));
    }

    // Ожидание остальных потомков (опционально)
    wait(NULL);
    wait(NULL);

    printf("Parent exiting\n");
    return 0;
}
