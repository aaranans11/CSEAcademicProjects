#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdbool.h>

#define CONTROLLER_FIFO_NAME "/tmp/controller_fifo"
#define DEVICE_FIFO_NAME "/tmp/device_%d_fifo"

#define ACK_MESSAGE = "ACK"
#define STOP_MESSAGE = "stop"

struct initial_device_data_to_pass {
    char device_type;
    char *device_name[50];
    int threshold;
    pid_t device_pid;
};

struct sensor_reading {
    pid_t device_pid;
    int current_reading;
};


