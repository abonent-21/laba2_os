#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    printf("Father: PID=%d, PPID=%d\n", getpid(), getppid());
    system("ps -l > father_processes.log"); // Сохраняем состояние процессов до fork()

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Дочерний процесс: заменяем его образ на son.out
        execl("./son", "son", NULL);
        perror("execl failed"); // Выполняется только при ошибке execl()
        exit(EXIT_FAILURE);
    } else {
        // Родительский процесс
        wait(NULL); // Ожидаем завершения потомка
        system("ps -l > father_after_wait.log"); // Состояние после завершения
        printf("Father: Child process finished.\n");
    }

    return 0;
}
