#include "time.h"
#include "platform_timer.h"

void TIMER::SystemTimerRun(void)
{
    // 1ms
    this->SystemTimerListRun(&this->task1msList);

    // 5ms
    if (!(this->systime1ms % 5))
        this->SystemTimerListRun(&this->task5msList);

    // 100ms
    if (!(this->systime1ms % 100))

        this->SystemTimerListRun(&this->task100msList);

    // 500ms
    if (!(this->systime1ms % 500))
        this->SystemTimerListRun(&this->task500msList);

    // 1000ms
    if (!(this->systime1ms % 1000))
        this->SystemTimerListRun(&this->task1000msList);

    this->systime1ms++;
}

void TIMER::SystemTimerListRun(LinkedList *list)
{
    Node *node = list->getHead();

    while (node)
    {
        TIMER_FUNC *task1ms = reinterpret_cast<TIMER_FUNC *>(node->index);

        task1ms->func((void *)task1ms->param);

        node = node->next;
    }
}

void TIMER::SystemTimerAddTask(uint16_t level, TIMER_CALLBACK_FPTR handler, void *param)
{
    TIMER_FUNC *pFunc = new TIMER_FUNC();

    pFunc->func = handler;
    pFunc->param = param;

    switch (level)
    {
    case TIMER1MS_CNT:
        this->task1msList.addNode(pFunc);
        break;
    case TIMER5MS_CNT:
        this->task5msList.addNode(pFunc);
        break;
    case TIMER100MS_CNT:
        this->task100msList.addNode(pFunc);
        break;
    case TIMER500MS_CNT:
        this->task500msList.addNode(pFunc);
        break;
    case TIMER1000MS_CNT:
        this->task1000msList.addNode(pFunc);
        break;
    default:
        free(pFunc);
        break;
    }
}