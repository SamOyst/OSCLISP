/* 
 * Author(s): Aidan (A00458881)
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_NAME "/prod_cons_buffer"

int main() {
    int shm_fd;
    int *buffer;
    int value;

    /* Get integer input from user */
    printf("Enter integer value to produce: ");
    if (scanf("%d", &value) != 1) {
        printf("Error: Invalid input. Only integers are accepted.\n");
        return 1;
    }

    /* Open existing shared memory (must be initialized first) */
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Error opening shared memory");
        return 1;
    }

    /* Map memory */
    buffer = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (buffer == MAP_FAILED) {
        perror("Memory mapping failed");
        return 1;
    

    /* Overwrite buffer with new value */
    *buffer = value;
    printf("Produced value = %d\n", *buffer);

    /* Cleanup */
    munmap(buffer, sizeof(int));
    close(shm_fd);

    return 0;
}
