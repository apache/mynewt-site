# Scheduler/Context Switching


Scheduler's job is to maintain the list of tasks and decide which one should be running next.

## Description

Task states can be *running*, *ready to run* or *sleeping*.

When task is *running*, CPU is executing in that task's context. The program counter (PC) is pointing to instructions task wants to execute and stack pointer (SP) is pointing to task's stack.

Task which is *ready to run* wants to get on the CPU to do its work.

Task which is *sleeping* has no more work to do. It's waiting for someone else to wake it up.

Scheduler algorithm is simple: from among the tasks which are ready to run, pick the the one with highest priority (lowest numeric value in task's t_prio field), and make its state *running*.

Tasks which are either *running* or *ready to run* are kept in linked list `g_os_run_list`. This list is ordered by priority.

Tasks which are *sleeping* are kept in linked list `g_os_sleep_list`.

Scheduler has a CPU architecture specific component; this code is responsible for swapping in the task which should be *running*. This process is called context switch. During context switching the state of the CPU (e.g. registers) for the currently *running* task is stored and the new task is swapped in.


## List of Functions


The functions available in context_switch are:

| **Function** | **Description** |
|-----------|-------------|
| [os_sched](os_sched.md) | Performs context switch if needed. |
| [os_arch_ctx_sw](os_arch_ctx_sw.md) | Change the state of task given task to *running*. |
| [os_sched_ctx_sw_hook](os_sched_ctx_sw_hook.md) | Performs task accounting when context switching. |
| [os_sched_get_current_task](os_sched_get_current_task.md) | Returns the pointer to task which is currently *running*. |
| [os_sched_insert](os_sched_insert.md) | Insert task into scheduler's ready to run list. |
| [os_sched_next_task](os_sched_next_task.md) | Returns the pointer to highest priority task from the list which are *ready to run*. |
| [os_sched_os_timer_exp](os_sched_os_timer_exp.md) | Inform scheduler that OS time has moved forward. |
| [os_sched_resort](os_sched_resort.md) | Inform scheduler that the priority of the given task has changed and the *ready to run* list should be re-sorted. |
| [os_sched_set_current_task](os_sched_set_current_task.md) | Sets the given task to *running*. |
| [os_sched_sleep](os_sched_sleep.md) | The given task's state is changed from *ready to run* to *sleeping*. |
| [os_sched_wakeup](os_sched_wakeup.md) | Called to make task *ready to run*. If task is *sleeping*, it is woken up. |
