#include <../include/led.h>


// 显示数字的函数
void LED_SEG::display_number(int number, uint8_t *list, uint8_t len)
{
  // 显示数字
  for (int i = 0; i < len; i++)
  {
    digitalWrite(list[i], logic_array[number][i]); // 段选线数组和数字电平
  }
}
