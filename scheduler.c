/*********************************************

SchedCreate:
    Allocate memory for the scheduler
    Allocate memory for the priority queue
    Initialize remaining fields in scheduler struct
    Return a pointer to the new scheduler

*********************************************

SchedDestroy:
    Check if the scheduler is not NULL
    Destroy the priority queue
    Free memory allocated for the scheduler

*********************************************

SchedAddTask:

    
    Create a new task
    Check if task uid is valid(not BAD_UID)
    Add the task to the priority queue
    Return the UID of the task
*********************************************

SchedRemoveTask:
 
    Remove the task from the priority queue and destroy it
    Return the status
*********************************************

SchedRun:

    Set to_stop flag to 0
    Run tasks in a loop until to_stop is set on or the schedule is empty:
        Get the next task from the priority queue
        Update Current_task
        Get Task Time to run
        Wait until execution time (current-interval)
        Execute the task
        Check if the task needs to be reinserted
        If no: 
        	destroy task
        if yes :
        	Update time 
        Enqueue Task to the queue 
        Reset current task
*********************************************

SchedStop:
    
    Set the to_stop flag to 1
    Return the status
*********************************************

SchedSize:
    
    Get the size of the priority queue
    Return the size
*********************************************

SchedIsEmpty:
    
    Check if the priority queue is empty
    Return True (1) or False (0)
*********************************************

SchedClear:
    
    Clear the priority queue
    Return the status

*********************************************/
#include <stdlib.h> /* malloc,free */
#include <stdio.h> /*fprintf*/
#include <assert.h>/*assert*/
#include <time.h>/*time_t*/
#include <unistd.h>/*sleep*/
#include "scheduler.h"

 struct scheduler 
{
    priority_ty *p_queue;
    task_ty *curr_task;
    int to_stop;
};


sched_ty *SchedCreate()
{

    sched_ty *new_sched = (sched_ty *)malloc(sizeof(sched_ty));

    if (NULL == new_sched)
    {
        fprintf(stderr,"%s\n","Memory Allocation Error!");
        return NULL;
    }

    new_sched->p_queue = PriorityCreate((cmp_func_ty)TaskIsBefore);

    if (NULL == new_sched->p_queue)
    {  
        fprintf(stderr,"%s\n","Memory Allocation Error!");
        free(new_sched);
        return NULL;
    }
    new_sched->curr_task = NULL;
    new_sched->to_stop = 0;

    return new_sched;
}

void SchedDestroy(sched_ty *scheduler)
{
    assert(NULL != scheduler);
    SchedClear(scheduler);
    PriorityDestroy(scheduler->p_queue);
    free(scheduler);
    scheduler = NULL;
    
}

uid_ty SchedAddTask(sched_ty *sched, sched_op_func_ty op_func, void *op_params, time_t interval_in_sec)
{
    task_ty *new_task = NULL;
    uid_ty task_id;

    assert(NULL != sched);

    new_task = TaskCreate(interval_in_sec, op_func, op_params);

    if (new_task == NULL)
    {
        return UIDGetBadUID();
    }

    task_id = TaskGetUID(new_task);

    if(UIDIsSame(UIDGetBadUID(),task_id))
    {
        return UIDGetBadUID();
    }


    if (SCHED_NO_ERROR != (sched_status_ty)PriorityEnqueue(sched->p_queue, new_task))
    {
        TaskDestroy(new_task);

        return UIDGetBadUID();
    }

    return task_id;
}

sched_status_ty SchedRemoveTask(sched_ty *sched, uid_ty uid)
{
    cmp_func_ty IsMatch = TaskIsMatch;
    

    assert(NULL != sched);

    TaskDestroy(PriorityErase(sched->p_queue, IsMatch, &uid));


    return SCHED_NO_ERROR;
}

void SchedRun(sched_ty *sched)
{


    assert(NULL != sched);

    sched->to_stop = 0;
    

    while (1 != sched->to_stop && (!PriorityIsEmpty(sched->p_queue)))
    {

        int task_runner_result=0;
        time_t sleep_time = 0;

        sched->curr_task = PriorityDequeue(sched->p_queue);
        sleep_time = TaskGetTimeToRun(sched->curr_task)-time(NULL);

        
        if(sleep_time > 0)
        {
                sleep(sleep_time);
        }

        task_runner_result = TaskRun(sched->curr_task);

        if(TASK_REPEAT == task_runner_result)
        {
            TaskUpdateTimeToRun(sched->curr_task);
            PriorityEnqueue(sched->p_queue,sched->curr_task);
            sched->curr_task = NULL;
        }
        else if(TASK_NO_REPEAT == task_runner_result)
        {
            TaskDestroy(sched->curr_task);
            sched->curr_task = NULL;

        }

    }
}
int SchedStop(sched_ty *sched)
{
    assert(NULL != sched);
    printf("Sched stop \n");
    sched->to_stop = 1;

    return 0;
}

size_t SchedSize(sched_ty *sched)
{
    assert(NULL != sched);

    return PrioritySize(sched->p_queue) + (sched->curr_task != NULL ? 1 : 0);
}

int SchedIsEmpty(sched_ty *sched)
{
    assert(NULL != sched);

    return PriorityIsEmpty(sched->p_queue) && (sched->curr_task == NULL);
}

void SchedClear(sched_ty *sched)
{

    task_ty *task = NULL;

    assert(NULL != sched);

    while (!PriorityIsEmpty(sched->p_queue))
    {
        task = PriorityDequeue(sched->p_queue);
        TaskDestroy(task);
    }

    if (sched->curr_task != NULL)
    {
        TaskDestroy(sched->curr_task);
        sched->curr_task = NULL;
    }

}
