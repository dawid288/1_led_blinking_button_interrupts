#include <stdio.h>
#include <stdlib.h>
#include <driver/gpio.h>
#include <driver/timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void GPIO_Init(void);
void GPIO_TogglePin(gpio_num_t gpio_num);
void TIM_Init(void);

static void przerwanie(void *arg)
{
    /*if (!gpio_get_level(4)) gpio_set_level(15, 1);
    else gpio_set_level(15, 0);*/
    GPIO_TogglePin(15);
   
}

void app_main(void)
{
    GPIO_Init();

    while(1)
    {   
        /*
        gpio_set_level(15, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(15, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        */
    }
}

void GPIO_Init(void)
{
    gpio_config_t io_init;
    io_init.intr_type = GPIO_INTR_DISABLE;
    io_init.mode = GPIO_MODE_INPUT_OUTPUT;
    io_init.pin_bit_mask = (1 << 15);
    io_init.pull_down_en = 0;
    io_init.pull_up_en = 0;
    gpio_config(&io_init);

    gpio_install_isr_service(0);
    io_init.intr_type = GPIO_INTR_ANYEDGE ;
    io_init.mode = GPIO_MODE_INPUT;
    io_init.pin_bit_mask = (1 << 4);
    io_init.pull_down_en = 0;
    io_init.pull_up_en = 1;
    gpio_config(&io_init);
    gpio_isr_handler_add(4, przerwanie, NULL);
}

void TIM_Init(void)
{
    timer_config_t tim_init;
    tim_init.divider = 16;
    tim_init.counter_dir = TIMER_COUNT_UP;
    tim_init.counter_en = TIMER_PAUSE;
    tim_init.alarm_en = TIMER_ALARM_EN;
    tim_init.auto_reload = 1;
    timer_init(0, 0, &tim_init);

}

void GPIO_TogglePin(gpio_num_t gpio_num)
{
    uint8_t value = gpio_get_level(gpio_num);
    gpio_set_level(gpio_num, ~value);

}
