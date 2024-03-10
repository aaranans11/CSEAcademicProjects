#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_CONSUMERS 4
#define NUM_PROCESSES 20
#define NUM_PROCESSES_PER_CPU 5
#define RQ0 0
#define RQ1 1
#define RQ2 2
#define BONUS 5

#define MAX(x, y) (((x) > (y)) ? (x) : (y)) 
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


struct pcb_struct {
	int pid;
	char sched_policy[20];
	int sp;
	int dp;
	int remain_time;
	int time_slice;
	int accu_time_slice;
	int last_cpu;
    int bonus;
};

struct queue_struct {
	struct pcb_struct queue[3][NUM_PROCESSES];
	int index;
    int count[3];
    int normal_count;
    int fifo_count;
    int rr_count;
};

char sched[20];
int prio;
int time1;

struct queue_struct RQ[NUM_CONSUMERS];
struct pcb_struct temp_pcb;

void *producer_function(void *arg);
void *consumer_function(void *arg);

void insertionSort(struct pcb_struct arr[], int n)
{
    int i, key, j;
    struct pcb_struct pcb_i;
    for (i = 1; i < n; i++) {
        pcb_i = arr[i];
        key = pcb_i.sp;
        j = i - 1;
 
        //Shift elements with higher priority than current key one index to the right       
        while (j >= 0 && arr[j].sp > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = pcb_i;
    }
}

void dynamicPrioritySort(struct pcb_struct arr[], int n)
{
    int i, key, j;
    struct pcb_struct pcb_i;
    for (i = 1; i < n; i++) {
        pcb_i = arr[i];
        key = pcb_i.dp;
        j = i - 1;
 
        //Shift elements with higher priority than current key one index to the right       
        while (j >= 0 && arr[j].dp > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = pcb_i;
    }
}

int main() {
    int res;
    int pid = 1000;
    pthread_t producer_thread;
    pthread_t consumer_threads[NUM_CONSUMERS];
    for(int i = 0; i < NUM_CONSUMERS; i++) {
        RQ[i].index = 0;
        for(int j = 0; j < 3; j++) {
            RQ[i].count[j] = 0;
        }
        RQ[i].normal_count = 0;
        RQ[i].fifo_count = 0;
        RQ[i].rr_count = 0;
    }
    void *thread_result;
    int array[NUM_CONSUMERS];
    
    //Create producer thread
    res = pthread_create(&producer_thread, NULL, producer_function, (void *)pid);

    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    //Join producer thread after all items added to buffer
    res = pthread_join(producer_thread, &thread_result);
    if (res == 0) {
        printf("Picked up producer thread\n");
    }
    else {
        perror("pthread_join failed");
    }
    
    //Create 4 consumer threads
	for(int i = 0; i < NUM_CONSUMERS; i++) {
		array[i] = i;
		res = pthread_create(&consumer_threads[i], NULL, consumer_function, (void *)&array[i]);
		if (res != 0) {
		    perror("Thread creation failed");
		    exit(EXIT_FAILURE);
		}
        //DEBUG
        sleep(2);
	}
	
	for(int i = NUM_CONSUMERS - 1; i >= 0; i--) {
        res = pthread_join(consumer_threads[i], &thread_result);
        if (res == 0) {
            printf("Picked up a consumer thread\n");
        }
        else {
            perror("pthread_join failed");
        }
    }
    exit(EXIT_SUCCESS);
}

void *producer_function(void *arg) {

    int thread_pid = 1000;
    printf("This is the producer.\n");
    
    FILE *textfile;
    
    //Read process information from input text file
    textfile = fopen("ass3Input.txt", "rb");
    if(textfile == NULL) {
        fprintf(stderr, "File open failed\n");
        exit(EXIT_FAILURE);
    }
    
    int temp_RQ_index[NUM_CONSUMERS][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    for(int i = 0; i < NUM_PROCESSES; i++){
            //Read scheduling policy, priority, and execution time from current line of text file
            fscanf (textfile, "%[^,],%d,%d\n", sched, &prio, &time1);
            
            //Initialize process information based on read process information
            temp_pcb.pid = thread_pid;
            strcpy(temp_pcb.sched_policy, sched);
            temp_pcb.sp = prio;
            temp_pcb.dp = 0;
            temp_pcb.remain_time = time1;
            temp_pcb.time_slice = 100;
            temp_pcb.accu_time_slice = 0;
            temp_pcb.bonus = BONUS;
            
            //Determine which RQ to insert process into
            int RQ_num = 0;
            if(temp_pcb.sp < 100) {
                RQ_num = RQ0;
            }
            else if(temp_pcb.sp < 130) {
                RQ_num = RQ1;
            }
            else {
                RQ_num = RQ2;
            }
            //Determine which CPU's RQ to insert process into to maintain 3:1:1 NORMAL:FIFO:RR ratio
            int RQ_insert_index = 0;    
            if(strcmp(temp_pcb.sched_policy, "NORMAL") == 0) {
                for(int i = 0; i < NUM_CONSUMERS; i++) {
                    if(RQ[i].normal_count < RQ[RQ_insert_index].normal_count && RQ[i].normal_count < 3) {
                        RQ_insert_index = i;
                    }
                }
                RQ[RQ_insert_index].normal_count++;
            }
            else if(strcmp(temp_pcb.sched_policy, "FIFO") == 0) {
                for(int i = 0; i < NUM_CONSUMERS; i++) {
                    if(RQ[i].fifo_count < RQ[RQ_insert_index].fifo_count && RQ[i].fifo_count < 1) {
                        RQ_insert_index = i;
                    }
                }
                RQ[RQ_insert_index].fifo_count++;
            }
            else if(strcmp(temp_pcb.sched_policy, "RR") == 0) {   
                for(int i = 0; i < NUM_CONSUMERS; i++) {
                    if(RQ[i].rr_count < RQ[RQ_insert_index].rr_count && RQ[i].rr_count < 1) {
                        RQ_insert_index = i;
                    }
                }
                RQ[RQ_insert_index].rr_count++;
            }
            //Insert process into CPU RQ
            RQ[RQ_insert_index].queue[RQ_num][temp_RQ_index[RQ_insert_index][RQ_num]] = temp_pcb;
            RQ[RQ_insert_index].count[RQ_num]++;
            //DEBUG
            printf("Producer added process to RQ%d of CPU%d at index %d\n", RQ_num, RQ_insert_index, temp_RQ_index[RQ_insert_index][RQ_num]);
            printf("Process information: ");
            printf("PID: %d, ", RQ[RQ_insert_index].queue[RQ_num][temp_RQ_index[RQ_insert_index][RQ_num]].pid);
            printf("Sched policy: %s, ", RQ[RQ_insert_index].queue[RQ_num][temp_RQ_index[RQ_insert_index][RQ_num]].sched_policy);
            printf("Static priority: %d, ", RQ[RQ_insert_index].queue[RQ_num][temp_RQ_index[RQ_insert_index][RQ_num]].sp);
            printf("Dynamic priority: %d, ", RQ[RQ_insert_index].queue[RQ_num][temp_RQ_index[RQ_insert_index][RQ_num]].dp);
            printf("Remaining time: %d, ", RQ[RQ_insert_index].queue[RQ_num][temp_RQ_index[RQ_insert_index][RQ_num]].remain_time);
            printf("Time slice: %d, ", RQ[RQ_insert_index].queue[RQ_num][temp_RQ_index[RQ_insert_index][RQ_num]].time_slice);
            printf("Accumulated time slice: %d\n", RQ[RQ_insert_index].queue[RQ_num][temp_RQ_index[RQ_insert_index][RQ_num]].accu_time_slice);
                        
            temp_RQ_index[RQ_insert_index][RQ_num]++;
            //Sort RQ based on highest priority after insert
            insertionSort(RQ[RQ_insert_index].queue[RQ_num], temp_RQ_index[RQ_insert_index][RQ_num]);
		
            thread_pid++;
        }

    fclose(textfile);   
    pthread_exit(NULL);
}

void *consumer_function(void *arg) {
    // Seed random number generator
    unsigned int seed = time(NULL);
    srand(seed);
    int thread_num = *(int *)arg;
    printf("This is CPU thread %d\n", thread_num);

    //Simulate local ready queue for CPU
    struct queue_struct local_RQ = RQ[thread_num];

    //Iterate through each RQ (RQ0, RQ1, RQ2)
    for(int RQ_num = 0; RQ_num < 3; RQ_num++) {
        //Iterate through RQ and select process to run
        printf("In RQ%d:\n", RQ_num);
        int j = 0;
        while(local_RQ.count[RQ_num] > 0) {
            printf("Process (PID = %d, sched policy = %s, priority = %d) selected for execution\n", local_RQ.queue[RQ_num][j].pid, local_RQ.queue[RQ_num][j].sched_policy, local_RQ.queue[RQ_num][j].sp);
            if(strcmp(local_RQ.queue[RQ_num][j].sched_policy, "RR") == 0) {
                printf("RR process before updating: ");
                printf("Time slice: %d, ", local_RQ.queue[RQ_num][j].time_slice);
                printf("Remaining time: %d, ", local_RQ.queue[RQ_num][j].remain_time);
                printf("Accumulated time slice: %d, ", local_RQ.queue[RQ_num][j].accu_time_slice);
                printf("Last CPU: %d\n", local_RQ.queue[RQ_num][j].last_cpu);

                //Calculate and update time_slice
                if(local_RQ.queue[RQ_num][j].sp < 120){
                    local_RQ.queue[RQ_num][j].time_slice = (140 - local_RQ.queue[RQ_num][j].sp) * 20;
                }
                else{
                    local_RQ.queue[RQ_num][j].time_slice = (140 - local_RQ.queue[RQ_num][j].sp) * 5;
                }

                //update last_cpu
                local_RQ.queue[RQ_num][j].last_cpu = thread_num;

                //Calculate and update remaining time
                //Generate random number for service time
                int service_time = (1 + (rand() % 10)) * (local_RQ.queue[RQ_num][j].time_slice / 5);
                //DEBUG
                printf("Simulated service time: %d\n", service_time);
                
                int execution_time = MIN(local_RQ.queue[RQ_num][j].time_slice, service_time);
                printf("Process running for %d ms\n", execution_time);
                usleep(execution_time);
                //Check if simulated service time is less than current time slice
                if(service_time < local_RQ.queue[RQ_num][j].time_slice) {
                    //Simulated service time is less than current time slice; move process to blocked state
                    printf("Process did not use entire time slice.  Moving process to blocked state...\n");
                    usleep(1000); //simulate moving process to blocked state
                }
                //update accu_time_slice
                local_RQ.queue[RQ_num][j].accu_time_slice += execution_time;

                local_RQ.queue[RQ_num][j].remain_time -= execution_time;

                printf("RR process after updating: ");
                printf("Time slice: %d, ", local_RQ.queue[RQ_num][j].time_slice);
                printf("Remaining time: %d, ", local_RQ.queue[RQ_num][j].remain_time);
                printf("Accumulated time slice: %d, ", local_RQ.queue[RQ_num][j].accu_time_slice);
                printf("Last CPU: %d\n", local_RQ.queue[RQ_num][j].last_cpu);
            }

            else if(strcmp(local_RQ.queue[RQ_num][j].sched_policy, "FIFO") == 0) {
                if(local_RQ.queue[RQ_num][j].remain_time > 0) {
                    printf("FIFO process: running to completion for %d ms\n", local_RQ.queue[RQ_num][j].remain_time);
                    usleep(local_RQ.queue[RQ_num][j].remain_time);
                    local_RQ.queue[RQ_num][j].remain_time = 0;
                }
            }

            else if(strcmp(local_RQ.queue[RQ_num][j].sched_policy, "NORMAL") == 0) {
                printf("NORMAL process before updating: ");
                printf("PID: %d, ", local_RQ.queue[RQ_num][j].pid);
                printf("Dynamic priority: %d, ", local_RQ.queue[RQ_num][j].dp);
                printf("Time slice: %d, ", local_RQ.queue[RQ_num][j].time_slice);
                printf("Remaining time: %d, ", local_RQ.queue[RQ_num][j].remain_time);
                printf("Accumulated time slice: %d, ", local_RQ.queue[RQ_num][j].accu_time_slice);
                printf("Last CPU: %d\n", local_RQ.queue[RQ_num][j].last_cpu);

                //Calculate and update dynamic priority value
                local_RQ.queue[RQ_num][j].dp = MAX(100, MIN((local_RQ.queue[RQ_num][j].sp - local_RQ.queue[RQ_num][j].bonus + 5), 139));
                //Re-sort RQ based on dynamic priority
                dynamicPrioritySort(local_RQ.queue[RQ_num], local_RQ.count[RQ_num]);

                while(local_RQ.queue[RQ_num][j].remain_time > 0) {
                    //Calculate and update time_slice
                    if(local_RQ.queue[RQ_num][j].sp < 120){
                        local_RQ.queue[RQ_num][j].time_slice = (140 - local_RQ.queue[RQ_num][j].sp) * 20;
                    }
                    else{
                        local_RQ.queue[RQ_num][j].time_slice = (140 - local_RQ.queue[RQ_num][j].sp) * 5;
                    }

                    //update last_cpu
                    local_RQ.queue[RQ_num][j].last_cpu = thread_num;

                    //Calculate and update remaining time
                    //Generate random number for service time
                    int service_time = (1 + (rand() % 10)) * (local_RQ.queue[RQ_num][j].time_slice / 5);
                    //DEBUG
                    // printf("Simulated service time: %d\n", service_time);
                    
                    int execution_time = MIN(local_RQ.queue[RQ_num][j].time_slice, service_time);
                    printf("Process running for %d ms\n", execution_time);
                    usleep(execution_time);
                    //Check if simulated service time is less than current time slice
                    if(service_time < local_RQ.queue[RQ_num][j].time_slice) {
                        //Give process bonus for dynamic priority calculation in next iteration
                        local_RQ.queue[RQ_num][j].bonus = 10;
                        //Simulated service time is less than current time slice; move process to blocked state
                        printf("Process did not use entire time slice.  Moving process to blocked state...\n");
                        usleep(1000); //simulate moving process to blocked state
                    }
                    else {
                        local_RQ.queue[RQ_num][j].bonus = 5;
                    }
                    //update accu_time_slice
                    local_RQ.queue[RQ_num][j].accu_time_slice += execution_time;

                    local_RQ.queue[RQ_num][j].remain_time -= execution_time;

                    printf("NORMAL process after updating: ");
                    printf("PID: %d, ", local_RQ.queue[RQ_num][j].pid);
                    printf("Dynamic priority: %d, ", local_RQ.queue[RQ_num][j].dp);
                    printf("Time slice: %d, ", local_RQ.queue[RQ_num][j].time_slice);
                    printf("Remaining time: %d, ", local_RQ.queue[RQ_num][j].remain_time);
                    printf("Accumulated time slice: %d, ", local_RQ.queue[RQ_num][j].accu_time_slice);
                    printf("Last CPU: %d\n", local_RQ.queue[RQ_num][j].last_cpu);
                }
                
            }

            if(local_RQ.queue[RQ_num][j].remain_time<= 0) {
                printf("Process (PID %d) done\n", local_RQ.queue[RQ_num][j].pid);
                local_RQ.count[RQ_num]--;
            }
            j = (j + 1) % local_RQ.count[RQ_num];
        }
    }
    pthread_exit(NULL);
}

