#include <stdlib.h>/*free , malloc*/
#include <stdio.h>/*fprintf*/
#include <assert.h>/*assert*/

#include "priority.h"
#include "sortedlist.h"

struct priority_queue
{
    sorted_list_ty *sorted_list;
};


priority_ty *PriorityCreate(cmp_func_ty compare_func)
{
    priority_ty *priority_queue=(priority_ty *)malloc(sizeof(priority_ty));

    if(NULL == priority_queue)
    {
        fprintf(stderr,"%s","Memory Allocation Error!");
        return NULL;
    }

    priority_queue->sorted_list=SortedListCreate(compare_func);

    if(NULL == priority_queue->sorted_list)
    {
        fprintf(stderr,"%s","Memory Allocation Error!");
        free(priority_queue);
        return NULL;
    }

    return priority_queue;
}



void PriorityDestroy(priority_ty *p_queue)
{
    assert(p_queue != NULL);

    SortedListDestroy(p_queue->sorted_list);
    free(p_queue);
    p_queue=NULL;
}

priority_queue_status_ty PriorityEnqueue(priority_ty *p_queue, void *data)
{
    assert(p_queue != NULL);
    assert(data != NULL);

    if(NULL == SortedListGetData(SortedListInsert(p_queue->sorted_list, data)))
    {
        return PRIORITY_GENERAL_ERR;
    }

    return PRIORITY_NO_ERROR;
}

void *PriorityDequeue(priority_ty *p_queue)
{
    void *data = NULL;
    assert(p_queue != NULL);
    assert(!PriorityIsEmpty(p_queue));

    data=PriorityPeek(p_queue);

    SortedListPopFront(p_queue->sorted_list);

    return data;
}

void *PriorityPeek(priority_ty *p_queue)
{
    assert(p_queue != NULL);
    assert(!PriorityIsEmpty(p_queue));

    return SortedListGetData(SortedListBegin(p_queue->sorted_list));
}

int PriorityIsEmpty(const priority_ty *p_queue) 
{
    assert(p_queue != NULL);

    return SortedListIsEmpty(p_queue->sorted_list);
}

size_t PrioritySize(const priority_ty *p_queue)
{
    assert(p_queue != NULL);

    return SortedListLength(p_queue->sorted_list);
}

void PriorityClear(priority_ty *p_queue)
{
    assert(p_queue != NULL);

    while(!SortedListIsEmpty(p_queue->sorted_list))
    {
        SortedListPopFront(p_queue->sorted_list);
    }
    
}

void *PriorityErase(priority_ty *p_queue, cmp_func_ty is_match, void *data)
{
    void *returned_data = NULL;
    sorted_list_iter_ty iter;
    assert(p_queue != NULL);
    assert(is_match != NULL);
    assert(data != NULL);
    iter = SortedListFindIf(SortedListBegin(p_queue->sorted_list),SortedListEnd(p_queue->sorted_list),is_match, data);

    returned_data = SortedListGetData(iter);
    SortedListRemove(p_queue->sorted_list, iter);

    return returned_data;
}
