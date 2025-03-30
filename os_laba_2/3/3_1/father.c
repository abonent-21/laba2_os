#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    printf("Father PID=%d\n", getpid());

    // Запуск son1, son2, son3
    pid_t son1, son2, son3;

    // Создание son1
    son1 = fork();
    if (son1 == 0) {
        execl("./son1.out", "son1.out", NULL);
        perror("execl son1 failed");
        exit(1);
    }

    // Создание son2
    son2 = fork();
    if (son2 == 0) {
        execl("./son2.out", "son2.out", NULL);
        perror("execl son2 failed");
        exit(1);
    }

    // Создание son3
    son3 = fork();
    if (son3 == 0) {
        execl("./son3.out", "son3.out", NULL);
        perror("execl son3 failed");
        exit(1);
    }

    sleep(1); // Даем время потомкам запуститься

    // Сохраняем состояние процессов до отправки сигналов
    system("ps -l > before_kill.log");

    // Отправка сигналов
    kill(son1, SIGTERM); // son1: реакция по умолчанию (завершение)
    kill(son2, SIGTERM); // son2: игнорирование сигнала
    kill(son3, SIGTERM); // son3: обработка сигнала
	
    	int status;
	waitpid(son1, &status, 0); // Ожидаем завершения son1
	waitpid(son3, &status, 0); // Ожидаем завершения son3
    sleep(1); // Ждем обработки сигналов

    // Сохраняем состояние процессов после
    system("ps -l > after_kill.log");

    // Завершение
    printf("Signals sent. Check before_kill.log and after_kill.log\n");
    return 0;
}
