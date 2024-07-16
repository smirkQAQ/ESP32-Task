#ifndef __LED_H__
#define __LED_H__

#include <Arduino.h>
#include "public.h"

#define pin_a 13
#define pin_b 12
#define pin_c 14
#define pin_d 2
#define pin_e 0
#define pin_f 4
#define pin_g 5
#define pin_dp 16

class LED_SEG
{
public:
    LED_SEG()
    {
        led_num = sizeof(this->led_list) / sizeof(this->led_list[0]);
    }
    int get_Led_num()
    {
        return led_num;
    }
    uint8_t *get_led_list()
    {
        return led_list;
    }

    void display_number(int number, uint8_t *list, uint8_t len);

private:
    uint8_t led_list[8] = {13, 12, 14, 2, 0, 4, 5, 16};
    uint8_t led_num;
};

#endif