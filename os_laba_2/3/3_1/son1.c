#include <stdio.h>
#include <unistd.h>

int main() {
    printf("son1: PID=%d\n", getpid());
    while (1) {
        sleep(1); // Бесконечный цикл
    }
    return 0;
}
