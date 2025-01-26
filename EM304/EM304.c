#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/interp.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"
#include "pico/cyw43_arch.h"



// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9


void init_watchdog() 
{
    // Enable the watchdog with a longer timeout (5 seconds) initially
    watchdog_enable(5000, 1);
}


//function to provide watchdog updates through sleep to prevent rebooting when unnecessary
void update_through_sleep(int multiplier) {
    int i;
    for (i = 0; i<multiplier; i++){
    sleep_ms(50);
    watchdog_update();
    }
}


int main() {
    stdio_init_all();

    //init watchdog with longer timeout   
init_watchdog();
  
    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }
watchdog_update(); // Update watchdog during initialization

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

watchdog_update();// Update watchdog during initialization

    // Interpolator example code
    interp_config cfg = interp_default_config();
    // Now use the various interpolator library functions for your use case
    // e.g. interp_config_clamp(&cfg, true);
    //      interp_config_shift(&cfg, 2);
    // Then set the config 
    interp_set_config(interp0, 0, &cfg);
    // For examples of interpolator use see https://github.com/raspberrypi/pico-examples/tree/master/interp

watchdog_update(); // Update watchdog during initialization

    // Timer example code - This example fires off the callback after 2000ms

    // For more examples of timer use see https://github.com/raspberrypi/pico-examples/tree/master/timer
watchdog_update();
    // Watchdog example code
    if (watchdog_caused_reboot()) {
        printf("Rebooted by Watchdog!\n");
        // Whatever action you may take if a watchdog caused a reboot
    }
    
watchdog_update();
    // Enable the watchdog, requiring the watchdog to be updated every 100ms or the chip will reboot
    // second arg is pause on debug which means the watchdog will pause when stepping through code
   
    
    // You need to call this function at least more often than the 100ms in the enable call to prevent a reboot



    printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
    printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));
    // For more examples of clocks use see https://github.com/raspberrypi/pico-examples/tree/master/clocks

    // Example to turn on the Pico W LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);  

//reduce watchdog timer to 150ms
watchdog_enable(150, 1);

watchdog_update(); // Update watchdog during initialization

    while (true) {
        printf("Hello, world! \n wifi + i2c + alarm + interpolator + timer + watchdog\n");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);  

        update_through_sleep(20);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);  

        update_through_sleep(40);
    }
}