#include <gpiod.h>
#include <unistd.h>
#include <syslog.h>

int main() {
    openlog("led-blink", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Opening gpiochip0...");
    struct gpiod_chip *chip = gpiod_chip_open_by_name("/dev/gpiochip0");
    if (!chip) {
        syslog(LOG_ERR, "Unable to open gpiochip0: %m");
        closelog();
        return 1;
    }

    syslog(LOG_INFO, "Getting GPIO 25...");
    struct gpiod_line *line = gpiod_chip_get_line(chip, 25);
    if (!line) {
        syslog(LOG_ERR, "Unable to get GPIO 25: %m");
        gpiod_chip_close(chip);
        closelog();
        return 1;
    }

    syslog(LOG_INFO, "Setting GPIO 25 as output...");
    if (gpiod_line_request_output(line, "led-blink", 0) < 0) {
        syslog(LOG_ERR, "Unable to set GPIO 25 as output: %m");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        closelog();
        return 1;
    }

    syslog(LOG_INFO, "Starting blink loop...");
    while (1) {
        syslog(LOG_INFO, "Setting GPIO 25 high");
        gpiod_line_set_value(line, 1);
        usleep(1000000);
        syslog(LOG_INFO, "Setting GPIO 25 low");
        gpiod_line_set_value(line, 0);
        usleep(1000000);
    }

    gpiod_line_release(line);
    gpiod_chip_close(chip);
    closelog();
    return 0;
}
