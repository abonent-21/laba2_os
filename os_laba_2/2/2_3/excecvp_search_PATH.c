#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    char *args[] = {"ls", "-l", "-a", NULL};

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child (execvp):\n");
        execvp("ls", args); // Ищет ls в PATH
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("Parent: Child process finished.\n");
    }

    return 0;
}
