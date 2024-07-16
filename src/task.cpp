#include <Ticker.h>
#include "../include/public.h"
#include "../include/led.h"
#include "../include/platform_system.h"
#include "../include/platform_timer.h"

Ticker ticker1; // 建立Ticker用于实现定时功能
LED_SEG led;
SYSTEM_OBJ pSystem;
TIMER timer_task;

// 定义一个包装函数
void SystemRunRemarksTaskWrapper(void *param)
{
  pSystem.SystemRunRemarksTask(param);
}

// 定时器中断函数
void timer_interrupt()
{
  timer_task.SystemTimerRun();
}

void display()
{
  static int i = 0;
  led.display_number(i++, led.get_led_list(), led.get_Led_num());
  if (i >= 10)
  {
    i = 0;
  }
}

void init()
{
  for (int i = 0; i < led.get_Led_num(); i++)
  {
    pinMode(led.get_led_list()[i], OUTPUT);
  }
  timer_task.SystemTimerAddTask(TIMER1MS_CNT, SystemRunRemarksTaskWrapper, NULL);
  pSystem.SystemTaskInstall(1000, display);
  ticker1.attach_ms(1, timer_interrupt);
}

// void loop()
// {
//   pSystem.SystemTaskProcess();
// }