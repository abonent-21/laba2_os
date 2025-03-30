#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    printf("son2: PID=%d\n", getpid());
    signal(SIGTERM, SIG_IGN); // Игнорируем SIGTERM
    while (1) {
        sleep(1);
    }
    return 0;
}
