// Main menu for Project
// @Author: Denzyl Albarracin (A00473792)
// @Author: Bhanu Prakash (A00468530)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_program(const char *program) {
    pid_t pid = fork();

    if(pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if(pid == 0) {
        execl(program, program, NULL);
        perror("execl failed");
        exit(1);
    }
    else {
        wait(NULL);
    }
}
// STILL WIP welcome for some help
int main() { 

    int choice;

    while (1) {
        printf("\n#==== Select Project =====#\n");
        printf("1. Fork-Based Task Executor System\n");
        printf("2. Producer-Consumer Simulation System\n");
        printf("3. Quit\n");
        printf("Please enter your choice: ");   

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");        
            while (getchar() != '\n');
            continue;
        }

        switch(choice) {
            case 1:
                // runs your fork executor
                run_program("./forkTaskExecutor");   
                break;

            case 2:
                // runs producer-consumer system
                run_program("./producer_consumer");  
                break;

            case 3: 
                return 0;

            default:
                printf("invalid choice try agian.\n");
        }
    }
    return 0;
}
