#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3
#define TIMEOUT 5

int main() {
    pid_t pids[NUM_CHILDREN];

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (pids[i] == 0) {
            printf("Child %d started with PID %d\n", i + 1, getpid());

            if (i == 1) {
                printf("Child %d simulating unresponsive process...\n", i + 1);
                while (1) {
                    sleep(1);
                }
            } else {
                sleep(2);
                printf("Child %d completed successfully.\n", i + 1);
                exit(0);
            }
        }
    }

    sleep(TIMEOUT);

    printf("\nChecking child processes...\n");

    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (waitpid(pids[i], NULL, WNOHANG) == 0) {
            printf("Child with PID %d is still running. Terminating...\n", pids[i]);
            kill(pids[i], SIGKILL);
            waitpid(pids[i], NULL, 0);
            printf("Child with PID %d terminated.\n", pids[i]);
        } else {
            printf("Child with PID %d already finished.\n", pids[i]);
        }
    }

    printf("\nAll child processes handled successfully.\n");

    return 0;
}
