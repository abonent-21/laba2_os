#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Дочерний процесс: запуск команды ls с аргументами
        printf("Child (execl):\n");
        execl("/bin/ls", "ls", "-l", "-a", NULL); // Полный путь к ls
        perror("execl failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("Parent: Child process finished.\n");
    }

    return 0;
}
