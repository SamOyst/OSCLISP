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

    /* Open existing shared memory (read-only) */
    shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        printf("Error: Shared memory not found. Run the initializer first.\n");
        return 1;
    }

    /* Map memory */
    buffer = mmap(0, sizeof(int), PROT_READ, MAP_SHARED, shm_fd, 0);
    if (buffer == MAP_FAILED) {
        perror("Memory mapping failed");
        return 1;
    }

    /* Read and display the current buffer value */
    printf("Consumed value = %d\n", *buffer);

    /* Cleanup */
    munmap(buffer, sizeof(int));
    close(shm_fd);

    return 0;
}
