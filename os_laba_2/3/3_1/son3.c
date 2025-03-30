#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig) {
    printf("son3: Received SIGTERM. Exiting...\n");
    printf("SIG: %d\n", sig);
    exit(0);
}

int main() {
    printf("son3: PID=%d\n", getpid());
    signal(SIGTERM, handler); // Устанавливаем обработчик
    while (1) {
        sleep(1);
    }
    return 0;
}
