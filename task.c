/*********************************************
TaskCreate:
    Allocate memory for a new task
    Initialize task_id using UIDGenerate()
    Initialize op_func with the provided function pointer
    Initialize op_params with the provided parameters
    Initialize interval_in_sec with the provided interval
    Initialize time_to_run based on the current time + interval
    Return a pointer to the new task

*********************************************

TaskDestroy:
    Check if the task is not NULL
    Free memory allocated for the task

*********************************************

TaskUpdateTimeToRun:
    Check if the task is not NULL
    Update time_to_run based on the current time + interval
    Return status, 0 for no error, 1 for error

*********************************************

TaskGetTimeToRun:

    Check if the task is not NULL
    Return time_to_run

*********************************************

TaskGetUID:

    Check if the task is not NULL
    Return task_id

*********************************************

TaskIsMatch:

    Check if the task is not NULL
    Compare task_id with the given task_id
    Return True(1) if they match, False(0) otherwise

*********************************************

TaskRun:

    Check if the task and op_func is not NULL
    Call the task's op_func with op_params
    Return status of whether to repeat the task (0 for not, 1 otherwise)

*********************************************

TaskIsBefore:

    Check if both tasks are not NULL
    Compare time_to_run of the first_task with the second_task
    Return True(1) if the first_task should happen before the second_task, False(0) otherwise


*********************************************/
#include <stddef.h>/*NULL*/
#include <time.h>/*time_t*/
#include <assert.h>/*assert*/
#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*malloc free*/

#include "task.h"

task_ty *TaskCreate(time_t interval_in_sec, task_op_func_ty op_func, void *op_params)
{
    task_ty *task = NULL;
    uid_ty uid;

    assert(0 < interval_in_sec);
    assert(NULL != op_func);

    task = (task_ty *)malloc(sizeof(task_ty));

    if(NULL == task)
    {
        fprintf(stderr, "%s\n","Memory Allocation Error!" );

        return NULL;
    }

    uid = UIDGenerate();
    task->task_id = uid;
    task->op_func = op_func;
    task->op_params = op_params;
    task->interval_in_sec = interval_in_sec;
    task->time_to_run = uid.time_stamp + interval_in_sec;


    return task;
}


void TaskDestroy(task_ty *task)
{
    if(NULL == task)
    {
        return;
    }

    free(task);

    task = NULL;
}

task_status_ty TaskUpdateTimeToRun(task_ty *task)
{
    assert(NULL != task);

    task->time_to_run = time(NULL) + task->interval_in_sec;

    if(-1 == task->time_to_run)
    {
        return ERROR;
    }

    return NO_ERROR;    
}

time_t TaskGetTimeToRun(task_ty *task)
{
    assert(NULL != task);

    return task->time_to_run;
}

uid_ty TaskGetUID(task_ty *task)
{
    assert(NULL != task);

    return task->task_id;
}

int TaskIsMatch(const void *task, const void *task_id)
{
    assert(NULL != task);

    return  UIDIsSame(((task_ty *)task)->task_id, *(uid_ty *)task_id)?0:1;/*magic*/
}

task_repeat_status_ty TaskRun(task_ty *task)
{
    int result = task->op_func(task->op_params);

    return result;
}

int TaskIsBefore(const void *first_task, const void *second_task)
{
    int return_val = 0;
    time_t res = ((task_ty *)first_task)->time_to_run - 
                                            ((task_ty *)second_task)->time_to_run;
    
    assert(NULL != first_task);
    assert(NULL != second_task);

    if(0 < res)
    {
        return_val = 1;
    }
    if(0 > res)
    {
        return_val = -1;
    }
    if(0 == res)
    {
        return_val =0;
    }

    return return_val;

}