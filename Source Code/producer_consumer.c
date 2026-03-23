/* 
 * Author (s): Ben Anderson (A00473343)
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_NAME "/prod_cons_buffer"

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

int main() {

    int shm_fd;
    int *buffer;

    /* Create shared memory */
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Error creating shared memory");
        return 1;
    }

    /* Set size = one */
    if (ftruncate(shm_fd, sizeof(int)) == -1) {
        perror("Error setting shared memory size");
        return 1;
    }

    /* Map memory */
    buffer = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (buffer == MAP_FAILED) {
        perror("Memory mapping failed");
        return 1;
    }

    /* Initialize */
    *buffer = 0;

    /* Confirmation message */
    printf("Shared buffer created successfully.\n");
    printf("Initial buffer value = %d\n", *buffer);

    int choice;
    while (1) {
        printf("\n#==== Select Project =====#\n");
        printf("1. Producer\n");
        printf("2. Consumer\n");
        printf("0. Quit\n");
        printf("Please enter your choice: ");   

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");        
            while (getchar() != '\n');
            continue;
        }

        switch(choice) {
            case 1:
                // runs your fork executor
                run_program("./producer");   
                break;

            case 2:
                // runs producer-consumer system
                run_program("./consumer");  
                break;

            case 0: 
                munmap(buffer, sizeof(int));
                close(shm_fd);
                return 0;

            default:
                printf("invalid choice try agian.\n");
        }
    }

    /* Cleanup */
    munmap(buffer, sizeof(int));
    close(shm_fd);

    return 0;
}