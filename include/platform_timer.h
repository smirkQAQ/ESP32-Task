#ifndef __PLATFORM_TIMER_H__
#define __PLATFORM_TIMER_H__

#include "public.h"
#include "platform_system.h"

#define TIMER1MS_CNT     1
#define TIMER5MS_CNT     5
#define TIMER100MS_CNT   100
#define TIMER500MS_CNT   500
#define TIMER1000MS_CNT  1000

typedef void (*TIMER_CALLBACK_FPTR)(void *);

class TIMER
{
public:
    uint32_t systime1ms;
    LinkedList task1msList;
    LinkedList task5msList;
    LinkedList task100msList;
    LinkedList task500msList;
    LinkedList task1000msList;

    void SystemTimerRun();
    void SystemTimerListRun(LinkedList *list);
    void SystemTimerAddTask(uint16_t level, TIMER_CALLBACK_FPTR handler, void *param);
};

class TIMER_FUNC
{
public:
    TIMER_CALLBACK_FPTR func;
    void *param;
};

#endif