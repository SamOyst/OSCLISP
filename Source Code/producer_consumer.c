/* 
 * Author (s): Ben Anderson (A00473343)
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

    /* Cleanup */
    munmap(buffer, sizeof(int));
    close(shm_fd);

    return 0;
}