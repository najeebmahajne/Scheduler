/*******************************************************************************
Project: Scheduler
Name: ---
Reviewer: ---
Date: 
Version: 1.0
*******************************************************************************/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h>/*size_t*/
#include <time.h>/*time_t*/

#include "priority.h"
#include "task.h"
#include "uid.h"

typedef enum
{
	SCHED_NO_ERROR = 0,
	SCHED_ERROR = 1
}sched_status_ty;

typedef struct scheduler sched_ty;
typedef int(*sched_op_func_ty)(void *op_params);
typedef int(*sched_cmp_func_ty)(const void *data1, const void *data2);


/*
Function Description: Create a new scheduler

Return value: pointer to the new scheduler

Undefined behaviour: None

Time Complexity: O(1)

on failure: NULL.
*/
sched_ty *SchedCreate();

/*
Function Description: Destroy a scheduler

Return value: None

Undefined behaviour: scheduler null

Time Complexity: O(n)

on failure: None.
*/
void SchedDestroy(sched_ty *schedler);

/*
Function Description: Add task to scheduler

Return value: uid of the task

Undefined behaviour: sched, op_func, op_params are NULL, interval_in_sec < 0.

Time Complexity: O(1)

on failure: BAD_UID.
*/
uid_ty SchedAddTask(sched_ty *sched, sched_op_func_ty op_func, 
										void *op_params, time_t interval_in_sec);

/*
Function Description: Remove task from scheduler by UID

Return value: Status, 0 for no issues

Undefined behaviour: sched is null or UID BAD_ID.

Time Complexity: O(n)

on failure: 1 on failure.
*/
sched_status_ty SchedRemoveTask( sched_ty *sched, uid_ty uid);

/*
Function Description: Start running tasks in scheduler

Return value: None.

Undefined behaviour:Sched null

Time Complexity: O(1)

on failure: None.
*/
void SchedRun( sched_ty *sched);

/*
Function Description: Update flag to_stop

Return value: none

Undefined behaviour:Sched null

Time Complexity: O(1)

on failure: none.
*/
int SchedStop( sched_ty *sched);

/*
Function Description: Return amount of tasks in scheduler

Return value: size

Undefined behaviour:Sched null

Time Complexity: O(n)

on failure: None
*/
size_t SchedSize( sched_ty *sched);

/*
Function Description: Return if empty

Return value: True(1) or False(0)

Undefined behaviour:Sched null

Time Complexity: O(1)

on failure: None
*/
int SchedIsEmpty( sched_ty *sched);

/*
Function Description: Remove all tasks

Return value: status, 0 for no error

Undefined behaviour:Sched null

Time Complexity: O(n)

on failure: None
*/
void SchedClear( sched_ty *sched);

#endif /*__SCHEDULER_H__*/