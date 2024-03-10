#include "shm_com.h"

int main()
{
    void *shared_memory = (void *)0;
    struct shared_mem_st *shared_buffer;
    int shmid;

    int sem_S_id;
    int sem_N_id;
    int sem_E_id;

    //Create shared memory
    shmid = shmget((key_t)1111, sizeof(struct shared_mem_st), 0666 | IPC_CREAT);

    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    //DEBUG
    printf("Shared memory created\n");

    //Make the shared memory accessible to the program (attach it to address space)
    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (int)shared_memory);

    //Assign the shared_memory segment to shared_buffer
    shared_buffer = (struct shared_mem_st *)shared_memory;

    //Create semaphore S for mutual exclusion
    sem_S_id = semget((key_t)2222, 1, 0666 | IPC_CREAT);
    if (!set_semvalue(sem_S_id, 1)) {
        fprintf(stderr, "Failed to initialize semaphore S\n");
        exit(EXIT_FAILURE);
    }

    //Create semaphore N for counting number of consumable items in shared memory buffer
    sem_N_id = semget((key_t)3333, 1, 0666 | IPC_CREAT);
    if (!set_semvalue(sem_N_id, 0)) {
        fprintf(stderr, "Failed to initialize semaphore N\n");
        exit(EXIT_FAILURE);
    }

    //Create semaphore E for counting number of empty spaces in shared memory buffer
    sem_E_id = semget((key_t)4444, 1, 0666 | IPC_CREAT);
    if (!set_semvalue(sem_E_id, NUM_BUFFER)) {
        fprintf(stderr, "Failed to initialize semaphore E\n");
        exit(EXIT_FAILURE);
    }

    int output_fd;
    int bytes_written = 0;

    //DEBUG
    printf("creating output file\n");

    //Open/create output text file to write into
    output_fd = open("output.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    if(output_fd == (int)NULL) {
        fprintf(stderr, "Failed to open output file\n");
        exit(EXIT_FAILURE);
    }

    shared_buffer->out_index = 0;
    int running = 1;
    while(running) {
        
        printf("Total bytes written is: %d", shared_buffer->file_size);
        
        //DEBUG
        printf("Issuing wait on semaphore N\n");

        //Issue wait on semaphore N (wait until there is something to consume from the buffer)
        if (!semaphore_p(sem_N_id)) exit(EXIT_FAILURE);

        //DEBUG
        printf("Issuing wait on semaphore S\n");

        //Issue wait on semaphore S (wait until producer is not in critical section writing to buffer)
        if (!semaphore_p(sem_S_id)) exit(EXIT_FAILURE);
        
        //Critical Section (take)
        //DEBUG
        printf("Writing from shared memory buffer to output file\n");

        //Write contents of shared memory buffer at current output index to output file
        //DEBUG
        printf("Contents of buffer[%d] to be written to output file:\n%s\n", shared_buffer->out_index, shared_buffer->buffers[shared_buffer->out_index].string);
        
        write(output_fd, shared_buffer->buffers[shared_buffer->out_index].string, strlen(shared_buffer->buffers[shared_buffer->out_index].string));
    
        //DEBUG
        printf("Number of bytes written to output file: %ld\n", strlen(shared_buffer->buffers[shared_buffer->out_index].string));

        //Clear contents of buffer at current index to indicate it is now empty
        memset(shared_buffer->buffers[shared_buffer->out_index].string, 0, BUFFER_SIZE);

        //Update output index
        shared_buffer->out_index = (shared_buffer->out_index + 1) % NUM_BUFFER;

        //Remainder Section
        //DEBUG
        printf("Issuing signal on semaphore S\n");

        //Issue signal on semaphore S to notify producer that consumer is no longer in critical section reading from buffer
        if (!semaphore_v(sem_S_id)) exit(EXIT_FAILURE);

        //DEBUG
        printf("Issuing signal on semaphore E\n");

        //Issue signal on semaphore E to update number of empty spaces in shared memory buffer
        if (!semaphore_v(sem_E_id)) exit(EXIT_FAILURE);

        //Update total number of bytes written to output file
        printf("Number of bytes added id %d", shared_buffer->buffers[shared_buffer->out_index].count);

        bytes_written += shared_buffer->buffers[shared_buffer->out_index].count;

        printf("Total bytes written is: %d", bytes_written);

        //Stop consuming if end of input file reached
        printf("File size is: %d", shared_buffer->file_size);
        if(bytes_written == (shared_buffer->file_size)) {
            printf("Code breaks here");
            break;
        }
        /*
        if(bytes_written >= shared_buffer->file_size) {
            running = 0;
        }
        */
    }

    //close(output_fd);

    printf("Total number of bytes written to output file: %d\n", bytes_written);

    sleep(10);
    //DEBUG
    printf("Deleting semaphores\n");

    //Delete Semaphores
    del_semvalue(sem_S_id);
    del_semvalue(sem_N_id);
    del_semvalue(sem_E_id);

    //DEBUG
    printf("Deleting and detaching shared memory\n");

    //Delete and detach shared memory
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}