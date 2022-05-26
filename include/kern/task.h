#ifndef KERN_TASK_H_
#define KERN_TASK_H_

#include "syscall.h"

#define NUM_TASKS 64
#define NUM_PRIORITY_LEVELS 8
#define USER_STACK_SIZE 0x20000  // 128 KB

struct TaskDescriptor {
  enum class State {
    kActive = 0,
    kReady,
    kZombie,
    kSendBlocked,
    kReceiveBlocked,
    kReplyBlocked,
    kEventBlocked
  };

  int tid;
  TaskDescriptor *parent;
  int priority;
  TaskDescriptor *nextReady;
  TaskDescriptor *nextSend;
  TaskDescriptor *lastSend;
  State state;
  int retVal;
  Trapframe tf;

  TaskDescriptor(TaskDescriptor *parent, int priority, int tid);
  TaskDescriptor();
  void enqueueSender(TaskDescriptor *sender);
  TaskDescriptor *dequeueSender();
};

class PriorityQueues {
  TaskDescriptor *heads[NUM_PRIORITY_LEVELS];
  TaskDescriptor *tails[NUM_PRIORITY_LEVELS];

 public:
  PriorityQueues();
  void enqueue(TaskDescriptor *task);
  TaskDescriptor *dequeue(int priority);
  TaskDescriptor *dequeue();
  bool isEmpty(int priority);
};

extern int tidCounter;
extern TaskDescriptor tasks[NUM_TASKS];
extern TaskDescriptor *curTask;
extern PriorityQueues readyQueues;

void taskBootstrap();

void taskStart(void (*fn)());

void taskCreate(Trapframe *tf);

void taskYield();

void taskExit();

int taskActivate(TaskDescriptor *task);

TaskDescriptor *taskSchedule();

bool isTidValid(int tid);

#endif  // KERN_TASK_H_
