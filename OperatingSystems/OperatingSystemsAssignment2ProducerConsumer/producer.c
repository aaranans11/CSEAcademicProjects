#include "shm_com.h"
int main(int argc, char **argv)
{
    if(argc < 2) {
        fprintf(stderr, "Input file name not provided\n");
        exit(EXIT_FAILURE);
    }
    void *shared_memory = (void *)0;
    struct shared_mem_st *shared_buffer;
    char input_buffer[BUFSIZ];

    int shmid;

    int sem_S_id;
    int sem_N_id;
    int sem_E_id;

    //Get shared memory

    //DEBUG
    printf("Getting shared memory\n");

    shmid = shmget((key_t)1111, sizeof(struct shared_mem_st), 0666 | IPC_CREAT);

    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    //Attach shared memory to address space

    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (int)shared_memory);

    //Assign the shared_memory segment to shared_buffer

    shared_buffer = (struct shared_mem_st *)shared_memory;

    //Get semaphore S for mutual exclusion
    sem_S_id = semget((key_t)2222, 1, 0666 | IPC_CREAT);

    //Get semaphore N for counting number of consumable items in shared memory buffer
    sem_N_id = semget((key_t)3333, 1, 0666 | IPC_CREAT);

    //Get semaphore E for counting number of empty spaces in shared memory buffer
    sem_E_id = semget((key_t)4444, 1, 0666 | IPC_CREAT);

    int input_fd;
    int nread;
    int input_file_size;
    int bytes_copied = 0;

    //DEBUG
    printf("Opening input text file\n");

    input_fd = open(argv[1], O_RDONLY);
    if(input_fd == (int)NULL) {
        fprintf(stderr, "Failed to open input file\n");
        exit(EXIT_FAILURE);
    }

    input_file_size = lseek(input_fd, 0, SEEK_END);
    lseek(input_fd, 0, SEEK_SET);
    //DEBUG
    printf("Input file size: %d\n", input_file_size);

    shared_buffer->in_index = 0;
    shared_buffer->file_size = input_file_size;
    int counter = 0;
    //Continuously read from input buffer until end of input file is reached
    while((nread = read(input_fd,input_buffer,sizeof(input_buffer))) > 0) {
        //DEBUG
        printf("Reading from input text file into input buffer\n");
        //DEBUG
        printf("nread = %d\n", nread);
        //DEBUG
        printf("Input buffer contents:\n%s\n", input_buffer);
        //DEBUG
        printf("Writing from input buffer to shared memory buffer\n");
        //Divide text stored in input buffer into smaller segments to be copied into shared memory buffer
        int i = 0;
        int min;
        
        while(i < nread) {
            if((nread-i) < BUFFER_SIZE){
                min = (nread - i);
            }
            else{
                min = BUFFER_SIZE;
            }
            //DEBUG
            printf("Issuing wait on semaphore E\n");

            //Issue wait on semaphore E (wait until enough empty spaces in buffer to produce)

            if (!semaphore_p(sem_E_id)) exit(EXIT_FAILURE);
            
            //DEBUG
            printf("Issuing wait on semaphore S\n");

            //Issue wait on semaphore S (wait until consumer is not in critical section reading from buffer)
            
            if (!semaphore_p(sem_S_id)) exit(EXIT_FAILURE);

            //Critical Section (append)

            //Copy contents of input buffer offset by number of bytes already copied into shared memory buffer
            strncpy(shared_buffer->buffers[shared_buffer->in_index].string, input_buffer + i, min);
            //DEBUG
            shared_buffer->buffers[shared_buffer->in_index].string[127] = '\0';
            //DEBUG
            printf("Contents written to buffer[%d]:\n%s\n", shared_buffer->in_index, shared_buffer->buffers[shared_buffer->in_index].string);

            //Update number of bytes written to current shared memory buffer and overall number of bytes written
            int bytes_in_buffer = strlen(shared_buffer->buffers[shared_buffer->in_index].string);
            //DEBUG
            printf("number of bytes written to buffer[%d]: %d\n", shared_buffer->in_index, bytes_in_buffer);

            shared_buffer->buffers[shared_buffer->in_index].count = bytes_in_buffer;
            counter += bytes_in_buffer;

            //Update input index
            shared_buffer->in_index = (shared_buffer->in_index + 1) % NUM_BUFFER;

            //Remainder Section
            //DEBUG
            printf("Issuing signal on semaphore S\n");

            //Issue signal on semaphore S to notify consumer that producer is no longer in critical section writing to buffer
            if (!semaphore_v(sem_S_id)) exit(EXIT_FAILURE);

            //DEBUG
            printf("Issuing signal on semaphore N\n");

            //Issue signal on semaphore N to update number of consumable items in shared memory buffer
            if (!semaphore_v(sem_N_id)) exit(EXIT_FAILURE);

            i += bytes_in_buffer;
            printf("Counter is: %d", bytes_in_buffer);  
            
        }
        bytes_copied += i;
        //DEBUG
        //printf("New number of bytes copied: %d\n", bytes_in_buffer);
    }
    
    printf("Input file size: %d\n", input_file_size);
    
    close(input_fd);

    printf("Total number of bytes written to shared memory buffer: %d\n", bytes_copied);
    sleep(15);
    //DEBUG
    if(bytes_copied != input_file_size) {
        printf("Error: input file contents not copied to buffer properly\n");
    }
 
    //Detach shared memory
    sleep(10);
    //DEBUG
    printf("Detaching shared memory\n");

    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}