#include "../include/platform_system.h"

void LinkedList::addNode(void *index)
{
    Node *newNode = new Node();
    newNode->index = index;
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        if (searchNode(index)) // 如果当前节点已经存在
        {
            return;
        }

        Node *temp = head;
        while (temp != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::deleteNode(void *index)
{
    // 头结点为空，直接返回
    if (head == nullptr)
        return;

    // 要删除头结点
    if (head->index == index)
    {
        Node *temp = new Node();
        head->next = temp;
        delete temp;
        return;
    }

    // 首先指向头结点，因为链表只能从头结点开始遍历
    Node *current = head;
    Node *previous = nullptr;
    while (current != nullptr && current->index != index) // 一直遍历直到要找到删除的那个结点
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) // 如果遍历完成后，找不到要遍历的结点
        return;

    previous->next = current->next;
    delete current;
}

// 修改节点
void LinkedList::updateNode(void *oldIndex, void *newIndex)
{
    if (searchNode(newIndex)) // 如果当前节点已经存在
    {
        return;
    }

    Node *temp = head;
    while (temp != nullptr && temp->index != oldIndex)
    {
        temp = temp->next;
    }

    if (temp != nullptr)
    {
        temp->index = newIndex;
    }
}

// 查询节点
bool LinkedList::searchNode(void *index)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->index == index)
            return true;
        temp = temp->next;
    }
    return false;
}

// 获取结点
Node *LinkedList::getNode(void *index)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->index == index)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

Node *LinkedList::getNextNode(Node *node)
{
    return node->next;
}

Node *LinkedList::getHead()
{
    if (head == nullptr)
        return nullptr;

    return head;
}

// 获取尾部节点
Node *LinkedList::getTail()
{
    if (head == nullptr)
        return nullptr;

    Node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    return temp;
}

LinkedList::~LinkedList()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
}

void SYSTEM_OBJ::SystemTaskInstall(uint16_t ivtTime, void (*taskHook)(void))
{
    if (this->taskComps.count == TASKS_MAX)
    {
        return;
    }

    this->taskComps.taskAttr[this->taskComps.count].run = 0;
    this->taskComps.taskAttr[this->taskComps.count].itvTime = ivtTime;
    this->taskComps.taskAttr[this->taskComps.count].timer = ivtTime;
    this->taskComps.taskAttr[this->taskComps.count].taskHook = taskHook;

    this->taskComps.count++;
}

void SYSTEM_OBJ::SystemRunRemarksTask(void *param)
{
    uint8_t i;
    for (i = 0; i < TASKS_MAX; i++)
    {
        if (this->taskComps.taskAttr[i].timer)
        {
            this->taskComps.taskAttr[i].timer--;
            if (this->taskComps.taskAttr[i].timer == 0) // 到达设定时间，运行该函数
            {
                this->taskComps.taskAttr[i].timer = this->taskComps.taskAttr[i].itvTime;
                this->taskComps.taskAttr[i].run = 1;
            }
        }
    }
}

void SYSTEM_OBJ::SystemTaskProcess()
{
    uint8_t i;
    for (i = 0; i < TASKS_MAX; i++)
    {
        if (this->taskComps.taskAttr[i].run)
        {
            this->taskComps.taskAttr[i].taskHook();
            this->taskComps.taskAttr[i].run = 0;
        }
    }
}

void SYSTEM_OBJ::SystemTaskDelete(void (*taskHook)(void))
{
    uint8_t index;
    if (this->taskComps.count > 0)
    {
        for (index = 0; index < this->taskComps.count; index++)
        {
            if (this->taskComps.taskAttr[index].taskHook == taskHook)
            {
                for (uint8_t move_index = index; move_index < this->taskComps.count - 1; move_index++)
                {
                    this->taskComps.taskAttr[move_index].taskHook = this->taskComps.taskAttr[move_index + 1].taskHook;
                    this->taskComps.taskAttr[move_index].itvTime = this->taskComps.taskAttr[move_index + 1].itvTime;
                    this->taskComps.taskAttr[move_index].timer = this->taskComps.taskAttr[move_index + 1].timer;
                    this->taskComps.taskAttr[move_index].run = this->taskComps.taskAttr[move_index + 1].run;
                }
                this->taskComps.count--; // 减少任务数量
            }
        }
    }
}
void SYSTEM_OBJ::SystemTaskTimeCtrl(uint16_t set_time, void (*taskHook)(void))
{
    uint8_t index;
    for (index = 0; index < this->taskComps.count; index++)
    {
        if (this->taskComps.taskAttr[index].taskHook == taskHook)
        {
            this->taskComps.taskAttr[index].timer = set_time;
            this->taskComps.taskAttr[index].itvTime = set_time;
        }
    }
}

void SYSTEM_OBJ::SystemTaskStateCtrl(uint16_t state, void (*taskHook)(void))
{
    uint8_t index;
    for (index = 0; index < this->taskComps.count; index++)
    {
        if (this->taskComps.taskAttr[index].taskHook == taskHook)
        {
            this->taskComps.taskAttr[index].run = state;
        }
    }
}

/**
 * @brieft
 *
 * @param state
 */
void SYSTEM_OBJ::SystemSetState(uint16_t state)
{
    this->runState |= state;
}

/**
 * @brief
 *
 * @return uint8_t
 */
uint16_t SYSTEM_OBJ::SystemGetState(void)
{
    return this->runState;
}

/**
 * @brief
 *
 * @return uint8_t
 */
void SYSTEM_OBJ::SystemCancelState(uint16_t state)
{
    this->runState &= ~state;
}