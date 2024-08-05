#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define FIRST_GPIO 2
#define OFFSET 7
#define BUTTON_GPIO (FIRST_GPIO + OFFSET)

int bits[10] = 
{
    0x3f,  // 0
    0x06,  // 1
    0x5b,  // 2
    0x4f,  // 3
    0x66,  // 4
    0x6d,  // 5
    0x7d,  // 6
    0x07,  // 7
    0x7f,  // 8
    0x67   // 9
};

int main() 
{
    int val = 0;

    stdio_init_all();
    printf("Hello World!!\n");

    for (int gpio = FIRST_GPIO; gpio < FIRST_GPIO + OFFSET; gpio++) 
    {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_OUT);                         
        gpio_set_outover(gpio, GPIO_OVERRIDE_INVERT);
    }

    gpio_init(BUTTON_GPIO);
    gpio_set_dir(BUTTON_GPIO, GPIO_IN);
    gpio_pull_up(BUTTON_GPIO);

    while (true) 
    {
        if (!gpio_get(BUTTON_GPIO)) 
            val = (val == 9) ? 0 : (val + 1);
        else if (val == 0) 
            val = 9;
        else 
            val--;

        int32_t mask = bits[val] << FIRST_GPIO;

        gpio_set_mask(mask);
        sleep_ms(250);
        gpio_clr_mask(mask);
    }
}
