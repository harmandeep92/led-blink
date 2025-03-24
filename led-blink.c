#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int ret;

    printf("Opening gpiochip0...\n");
    chip = gpiod_chip_open_by_name("gpiochip0");
    if (!chip) {
        perror("Unable to open gpiochip0");
        return 1;
    }

    printf("Getting GPIO 24...\n");
    line = gpiod_chip_get_line(chip, 24);
    if (!line) {
        perror("Unable to get GPIO 24");
        gpiod_chip_close(chip);
        return 1;
    }

    printf("Setting GPIO 24 as output...\n");
    ret = gpiod_line_request_output(line, "led-blink", 0);
    if (ret < 0) {
        perror("Unable to set GPIO 24 as output");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        return 1;
    }

    printf("Starting blink loop...\n");
    while (1) {
        printf("Setting GPIO 24 high\n");
        gpiod_line_set_value(line, 1);
        usleep(500000);
        printf("Setting GPIO 24 low\n");
        gpiod_line_set_value(line, 0);
        usleep(500000);
    }

    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return 0;
}
