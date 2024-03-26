#include <stddef.h>/*size_t*/
#include <stdio.h>/*printf*/
#include "scheduler.h"

typedef int (*test_function)();

static int Runner();
static int SchedCreateTest();
static int SchedDestroyTest();
static int SchedAddTaskTest();
static int SchedRemoveTaskTest();
static int SchedRunTest();
static int SchedStopTest();
static void PrintTestResult(const char* test_name, int status);
static int PrintHelloWorld(void *params);
static int PrintValue(void *params);
static int PrintValue1(void *params);
int main()
{
    if (SCHED_NO_ERROR == Runner())
    {
        printf("All tests passed successfully!\n");
    }
    else
    {
        printf("One or more tests failed.\n");
    }

    return SCHED_NO_ERROR;
}

static int Runner()
{
    size_t i=0;
    int status = 1;

    test_function test_functions[] = {
        SchedCreateTest,
        SchedAddTaskTest,
        SchedDestroyTest,
        SchedRemoveTaskTest,
        SchedStopTest,
        SchedRunTest,
        
    };

    const char* test_names[] = {
        "SchedCreateTest",
        "SchedAddTaskTest",
        "SchedDestroyTest",
        "SchedRemoveTaskTest",
        "SchedStopTest",
        "SchedRunTest",
        
    };
    
    
    for (i=0;i< sizeof(test_functions)/sizeof(test_functions[0]);++i)
    {
        status = test_functions[i]();
        PrintTestResult(test_names[i], status);
        if (SCHED_NO_ERROR != status)
        {
            return SCHED_ERROR;
        }
    }

    return SCHED_NO_ERROR;
}

static int SchedCreateTest()
{
    sched_ty *new_sched = SchedCreate();

    if (NULL == new_sched)
    {
        return SCHED_ERROR;
    }

    SchedDestroy(new_sched);

    return SCHED_NO_ERROR;
}
static int SchedDestroyTest()
{
    sched_ty *new_sched = SchedCreate();

    SchedDestroy(new_sched);

    return SCHED_NO_ERROR;
}

static int SchedAddTaskTest()
{
    sched_ty *sched = SchedCreate();
    uid_ty uid;

    uid = SchedAddTask(sched, (sched_op_func_ty)printf, "Hello, World!\n", 2);
    printf("Size: %lu \n",SchedSize(sched));

    if (UIDIsSame(uid, UIDGetBadUID()))
    {
        SchedDestroy(sched);
        return SCHED_ERROR;
    }

    SchedDestroy(sched);

    return SCHED_NO_ERROR;
}

static int SchedRemoveTaskTest()
{
    sched_ty *sched = SchedCreate();
    uid_ty uid;

    if (NULL == sched)
    {
        return SCHED_ERROR;
    }

    uid = SchedAddTask(sched, PrintHelloWorld, NULL, 2);


    
    if (UIDIsSame(uid, UIDGetBadUID()))
    {
        SchedDestroy(sched);
        return SCHED_ERROR;
    }

    if (SCHED_NO_ERROR != SchedRemoveTask(sched, uid))
    {
        SchedDestroy(sched);
        return SCHED_ERROR;
    }

    SchedDestroy(sched);

    return SCHED_NO_ERROR;
}

static int SchedRunTest()
{
    sched_ty *sched = SchedCreate();
    uid_ty uid;

    if (NULL == sched)
    {
        return SCHED_ERROR;
    }

    SchedAddTask(sched, (sched_op_func_ty)SchedStop, sched,6);
    uid = SchedAddTask(sched, PrintHelloWorld, NULL, 60);
    printf("Size: %lu \n",SchedSize(sched));
    uid = SchedAddTask(sched, PrintValue1, NULL, 2);
    uid = SchedAddTask(sched, PrintValue, NULL, 5);

    if (UIDIsSame(uid, UIDGetBadUID()))
    {
        SchedDestroy(sched);
        return SCHED_ERROR;
    }
    SchedRun(sched);

    
    SchedDestroy(sched);

    return SCHED_NO_ERROR;
}

static int PrintHelloWorld(void *params)
{
    (void)params;

    printf("Every 1 \n");

    return 1;
}

static int PrintValue(void *params)
{
    (void)params;
    printf("Every 5 \n");

    return 1;
}

static int PrintValue1(void *params)
{
    (void)params;
    printf("Every 2 \n");

    return 1;
}

static int SchedStopTest()
{
    sched_ty *sched = SchedCreate();
    


    if (NULL == sched)
    {
        return SCHED_ERROR;
    }

    SchedAddTask(sched, PrintHelloWorld, NULL, 1);
    SchedAddTask(sched, PrintValue, NULL, 2);
    SchedAddTask(sched, (sched_op_func_ty)SchedStop, sched, 3);
    SchedRun(sched);

    SchedDestroy(sched);
    return SCHED_NO_ERROR;
}

static void PrintTestResult(const char* test_name, int status)
{
    if (0 == status)
    {
        printf("%s: Passed\n", test_name);
    }
    else
    {
        printf("%s: Failed (Error Code: %d)\n", test_name, status);
    }
}