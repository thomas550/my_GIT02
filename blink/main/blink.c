/* Blink Example sal
 * Das originale blink-example von espressif
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO
uint32_t i=300 ;
void blink_task(void *pvParameter)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    printf("##### blink_task#####\n");

    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
        printf("##### blink_LOW %d \n",i++);
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO, 0);
//        vTaskDelay(2200 / portTICK_PERIOD_MS);
        vTaskDelay(i / portTICK_PERIOD_MS);
        printf("#####       blink_ HIGH %d\n",i);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
//        vTaskDelay(300 / portTICK_PERIOD_MS);
        vTaskDelay((i-300) / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    printf("\r#|#|###########################################|#\n");
    printf("Hallo Welt!\n");
    printf(" sa, 13.09.2017\n");
    printf("Software aus Spandau\r\n");
    printf("program: d:/uprozessorWS/ESP32_IDF_WS/blink\n");
    printf("Beispiel aus esp-idf/examples\n");
    printf("angepasst, ver�ndert, kodiert in Eclipse Oxygen Release (4.7.0)\r\r\n");
  //  printf("Beispiel aus esp-idf/examples\n");
   printf("   > Ein Task --blink_task-- wird erzeugt\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    printf("   > peng, fertig\r\n");
    printf("   > end of app_main() \r\n\n");

//    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
    xTaskCreate(&blink_task, "blink_task", 2048, NULL, 5, NULL);
}
