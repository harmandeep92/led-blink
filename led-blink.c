#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

#define GPIO 25

int main() {
    // Initialize syslog for logging
    openlog("led-blink", LOG_PID | LOG_CONS, LOG_USER);

    // Construct sysfs paths for GPIO 25
    char direction_path[50];
    char value_path[50];
    sprintf(direction_path, "/sys/class/gpio/gpio%d/direction", GPIO);
    sprintf(value_path, "/sys/class/gpio/gpio%d/value", GPIO);

    // Set GPIO direction to output
    syslog(LOG_INFO, "Setting GPIO %d as output...", GPIO);
    FILE *dir_file = fopen(direction_path, "w");
    if (!dir_file) {
        syslog(LOG_ERR, "Unable to open direction file %s: %s", direction_path, strerror(errno));
        closelog();
        return 1;
    }
    if (fprintf(dir_file, "out") < 0) {
        syslog(LOG_ERR, "Unable to set GPIO %d direction to out: %s", GPIO, strerror(errno));
        fclose(dir_file);
        closelog();
        return 1;
    }
    fclose(dir_file);

    // Blink loop
    syslog(LOG_INFO, "Starting blink loop...");
    while (1) {
        // Set GPIO high (LED on)
        FILE *val_file = fopen(value_path, "w");
        if (!val_file) {
            syslog(LOG_ERR, "Unable to open value file %s: %s", value_path, strerror(errno));
            sleep(1); // Prevent busy looping on error
            continue;
        }
        if (fprintf(val_file, "1") < 0) {
            syslog(LOG_ERR, "Unable to set GPIO %d to 1: %s", GPIO, strerror(errno));
        } else {
            syslog(LOG_INFO, "Setting GPIO %d high", GPIO);
        }
        fclose(val_file);
        sleep(1); // 1-second delay (equivalent to usleep(1000000))

        // Set GPIO low (LED off)
        val_file = fopen(value_path, "w");
        if (!val_file) {
            syslog(LOG_ERR, "Unable to open value file %s: %s", value_path, strerror(errno));
            sleep(1); // Prevent busy looping on error
            continue;
        }
        if (fprintf(val_file, "0") < 0) {
            syslog(LOG_ERR, "Unable to set GPIO %d to 0: %s", GPIO, strerror(errno));
        } else {
            syslog(LOG_INFO, "Setting GPIO %d low", GPIO);
        }
        fclose(val_file);
        sleep(1); // 1-second delay
    }

    // Cleanup (unreachable due to infinite loop, but included for completeness)
    closelog();
    return 0;
}