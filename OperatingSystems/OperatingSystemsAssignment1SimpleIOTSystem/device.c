#include <stdio.h>
#include <stdlib.h>
#include "device.h"

//Creates a new structure containing the device's data to be passed to the controller
struct initial_device_data_to_pass initialize_new_device_data(char *device_type, char* device_name, int threshold)
{
    struct initial_device_data_to_pass new_device_data;
    new_device_data.device_type = *device_type;
    *new_device_data.device_name = device_name;
    new_device_data.device_pid = getpid();
    new_device_data.threshold = threshold;

    return new_device_data;
}

/*
//Creates a new structure containing the actuator's data to be passed to the controller
struct initial_actuator_data_to_pass initialize_new_actuator_data(char* device_name)
{
    struct initial_actuator_data_to_pass new_actuator_data;
    *new_actuator_data.device_name = device_name;
    new_actuator_data.device_pid = getpid();
    
    return new_actuator_data;
}
*/

int main(int argc, char **argv)
{
    int controller_fifo_fd, device_fifo_fd;
    char device_fifo[256];

    //DEBUG
    printf("In device process\n");
    printf("Establishing device connection with controller\n");

    controller_fifo_fd = open(CONTROLLER_FIFO_NAME, O_WRONLY);
    if (controller_fifo_fd == -1) {
        fprintf(stderr, "Sorry, no controller\n");
        exit(EXIT_FAILURE);
    }

    //DEBUG
    printf("Controller FIFO opened in write only mode\n");

    sprintf(device_fifo, DEVICE_FIFO_NAME, getpid());
    if (mkfifo(device_fifo, 0777) == -1) {
        fprintf(stderr, "Sorry, can't make %s\n", device_fifo);
        exit(EXIT_FAILURE);
    }

    //DEBUG
    printf("Device fifo made\n");

    //DEBUG
    printf("Initializing device data to be passed to controller\n");

    //Create a new structure containing the device's data to be passed to the controller

    struct initial_device_data_to_pass new_device_data_to_pass = initialize_new_device_data(argv[1], argv[2], atoi(argv[3]));
    
    //DEBUG
    printf("Device type: %c\n", new_device_data_to_pass.device_type);
    printf("Device name: %s\n", *new_device_data_to_pass.device_name);
    printf("Device PID: %d\n", new_device_data_to_pass.device_pid);
    printf("Device threshold: %d\n", new_device_data_to_pass.threshold);

    //DEBUG
    printf("Writing device data to controller via FIFO\n");

    write(controller_fifo_fd, &new_device_data_to_pass, sizeof(new_device_data_to_pass));
    
    if (strcmp(new_device_data_to_pass.device_type, "s" == 0)) {
        bool sensor_stopped = false;
        struct sensor_reading sensor_reading_to_pass;
        sensor_reading_to_pass.device_pid = initial_device_data_to_pass.device_pid;
        //Start generating random sensor readings to send to the controller
        while (!sensor_stopped) {
            sensor_reading_to_pass.current_reading = rand() % 50;
            write(controller_fifo_fd, &sensor_reading_to_pass, sizeof(sensor_reading_to_pass));
        }
        
    }
    close(device_fifo_fd);
    unlink(device_fifo);
    exit(EXIT_SUCCESS);
}
