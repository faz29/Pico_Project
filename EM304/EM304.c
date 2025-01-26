#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/interp.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"
#include "pico/cyw43_arch.h"
#include "initialise_functions.h"


int main() {
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // Interpolator example code
    interp_config cfg = interp_default_config();
    // Now use the various interpolator library functions for your use case
    // Then set the config 
    interp_set_config(interp0, 0, &cfg);
    // For examples of interpolator use see https://github.com/raspberrypi/pico-examples/tree/master/interp

    sleep_ms(10000);
    i2c_initialisation(i2c0,400*1000,I2C_SDA,I2C_SCL);

    while (true) {
        printf("Hello, world! \n wifi + i2c + alarm + interpolator + timer + watchdog\n");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);  
        sleep_ms(250);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);  
        sleep_ms(500);

    }
}