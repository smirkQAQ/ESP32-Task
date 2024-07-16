#ifndef __PLATFORM_SYSTEM__H
#define __PLATFORM_SYSTEM__H

#include "Arduino.h"

#define TASKS_MAX 10

enum _SYSTEM_RUN_STATE
{
    SYSTEM_STATE_INIT = 1 << 0,
    SYSTEM_STATE_RUN = 1 << 1,
    SYSTEM_STATE_EE_FAULT = 1 << 2,
    SYSTEM_STATE_TIME_INIT = 1 << 3,
    SYSTEM_COMM_OK = 1 << 4,
    SYSTEM_COMM_ERROR = 1 << 5
};

// 链表
// 节点类
class Node
{
public:
    void *index;
    Node *next;

    Node()
    {
        index = NULL;
        next = NULL;
    }
};

// 链表类
class LinkedList
{
private:
    Node *head;

public:
    LinkedList() : head(nullptr) {};

    void addNode(void *index);

    void deleteNode(void *index);

    // 修改节点
    void updateNode(void *oldIndex, void *newIndex);

    // 查询节点
    bool searchNode(void *index);
    // 获取结点
    Node *getNode(void *index);

    // 获取下一节点
    Node *getNextNode(Node *node);
    // 获取头部节点
    Node *getHead();
    // 获取尾部节点
    Node *getTail();

    ~LinkedList();
};

class SYSTEM_TASK
{
public:
    uint8_t run;
    uint16_t timer;
    uint16_t itvTime;
    void (*taskHook)(void);
};

class TASK_COMPONENTS
{
public:
    uint8_t count;
    SYSTEM_TASK taskAttr[TASKS_MAX];
};

class SYSTEM_OBJ
{
public:
    SYSTEM_OBJ()
    {
        runState = SYSTEM_STATE_INIT;
    }

    uint8_t runState;
    TASK_COMPONENTS taskComps;

    void SystemTaskInstall(uint16_t ivtTime, void (*taskHook)(void));
    void SystemRunRemarksTask(void *param);
    void SystemTaskProcess(void);
    void SystemTaskDelete(void (*taskHook)(void));
    void SystemTaskTimeCtrl(uint16_t set_time, void (*taskHook)(void));
    void SystemTaskStateCtrl(uint16_t state, void (*taskHook)(void));

    void SystemSetState(uint16_t state);
    uint16_t SystemGetState(void);
    void SystemCancelState(uint16_t state);
};

#endif