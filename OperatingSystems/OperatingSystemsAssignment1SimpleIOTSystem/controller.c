#include "device.h"
#include <ctype.h>

void alert_actuator(int sig)
{

}

int main() {
    int controller_fifo_fd, device_fifo_fd;
    int read_res;
    pid_t pid;
    int num_devices = 0;
    struct initial_device_data_to_pass device_registration_data[3];
    
    struct sigaction act;
    
    act.sa_handler = alert_actuator;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    //int current_reading_sensor1, current_reading_sensor2 = 0;

    //DEBUG
    printf("In controller process\n");
    printf("Creating controller FIFO and opening controller FIFO in RDONLY mode\n");

    mkfifo(CONTROLLER_FIFO_NAME, 0777);
    controller_fifo_fd = open(CONTROLLER_FIFO_NAME, O_RDONLY);
    if (controller_fifo_fd == -1) {
        fprintf(stderr, "Controller fifo failure\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
	switch(pid) 
	{
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            //In child process (Device)
            
            //DEBUG
            sleep(5);
            printf("In child process (Device)\n");
            
            //Read the devices' initial data and store it in an array using indexes to identify each device
            while (num_devices < 3) {
                do {
                    read_res = read(controller_fifo_fd, &device_registration_data[num_devices], sizeof(device_registration_data[num_devices]));

                    if (read_res > 0) {
                        
                        //DEBUG
                        printf("Device data recieved by controller\n");
                        printf("Device type :%c\n", device_registration_data[num_devices].device_type);
                        //printf("Device name: %s\n", *device_registration_data[num_devices].device_name);
                        printf("Device PID: %d\n", device_registration_data[num_devices].device_pid);
                        printf("Device threshold: %d\n", device_registration_data[num_devices].threshold);
                        
                        num_devices ++;
                        }
                    //DEBUG
                    printf("Number of devices: %d\n", num_devices);
                    } while (read_res > 0);                
            }
            struct sensor_reading sensor_reading_received;

            bool threshold_reached = false;
            while (!threshold_reached) {
                do {
                    read_res = read(controller_fifo_fd, &sensor_reading_received, sizeof(sensor_reading_received));

                    if (read_res > 0) {
                        
                        //DEBUG
            
                        }
                    
                    } while (read_res > 0);        
            }
            /*
            struct initial_device_data_to_pass actuator;
            int i = 0; 
            while (i < 3) {
                if (strcmp(&device_registration_data[i].device_type, "a") == 0) {
                    actuator = device_registration_data[i];
                    break;
                }
                i++;
            }

            struct initial_device_data_to_pass sensor1 = device_registration_data[(i + 1) % 3]; 
            struct initial_device_data_to_pass sensor2 = device_registration_data[(i + 2) % 3];

            //DEBUG
            printf("Actuator data:\n");
            printf("Actuator type :%c\n", actuator.device_type);
            printf("Actuator PID: %d\n", actuator.device_pid);
            printf("Actuator threshold: %d\n", actuator.threshold);

            printf("Sensor 1 data:\n");
            printf("Sensor 1 type :%c\n", sensor1.device_type);
            printf("Sensor 1 PID: %d\n", sensor1.device_pid);
            printf("Sensor 1 threshold: %d\n", actuator.threshold);

            printf("Sensor 2 data:\n");
            printf("Sensor 2 type :%c\n", sensor2.device_type);
            printf("Sensor 2 PID: %d\n", sensor2.device_pid);
            printf("Sensor 2 threshold: %d\n", sensor2.threshold);
            */


            
    }
    close(controller_fifo_fd);
    unlink(CONTROLLER_FIFO_NAME);
    exit(EXIT_SUCCESS);
}