#include <stdlib.h>/*malloc , free*/
#include <assert.h>/*assert*/
#include <stdio.h>/*fprintf*/


#include "sortedlist.h"

#define ISEQUAL 1
#define NOT_EMPTY 0

struct sorted_list
{
  dlist_ty *dlist;
  cmp_func_ty compare_func;
};


sorted_list_ty *SortedListCreate(cmp_func_ty cmp_func)
{
	sorted_list_ty *sorted_list=NULL;

	assert(NULL != cmp_func);

	sorted_list=(sorted_list_ty *)malloc(sizeof(sorted_list_ty));

	if(NULL == sorted_list)
	{
		fprintf(stderr,"%s","Memory Allocation Error!");
		return NULL;
	}

	sorted_list->dlist = DListCreate();

	if(NULL == sorted_list->dlist)
	{
		fprintf(stderr,"%s","Memory Allocation Error!");
		free(sorted_list);
		return NULL;
	}

	sorted_list->compare_func = cmp_func;

	return sorted_list;
}

void SortedListDestroy(sorted_list_ty *sorted_list)
{
	assert(NULL != sorted_list);

	DListDestroy(sorted_list->dlist);
	sorted_list->dlist = NULL;

	free(sorted_list);
	sorted_list = NULL;
}

sorted_list_status_ty SortedListPopFront(sorted_list_ty *sorted_list)
{
	sorted_list_status_ty pop_list_status=SORTED_NO_ERROR;

	assert(NULL != sorted_list);
	assert(NULL != sorted_list->dlist);

	pop_list_status=(sorted_list_status_ty)DListPopFront(sorted_list->dlist);

	if(SORTED_NO_ERROR != pop_list_status)
	{
		return SORTED_GENERAL_ERR;
	}

	return pop_list_status;
}

sorted_list_status_ty SortedListPopBack(sorted_list_ty *sorted_list)
{
	sorted_list_status_ty pop_list_status=SORTED_NO_ERROR;

	assert(NULL != sorted_list);
	assert(NULL != sorted_list->dlist);

	pop_list_status=(sorted_list_status_ty)DListPopBack(sorted_list->dlist);

	if(pop_list_status != SORTED_NO_ERROR)
	{
		return SORTED_GENERAL_ERR;
	}

	return pop_list_status; 
}


size_t SortedListLength(const sorted_list_ty *sorted_list)
{
	size_t count = 0;

	assert(NULL != sorted_list);
	assert(NULL != sorted_list->dlist);

	count = DListLength(sorted_list->dlist);

	return count;
}

int SortedListIsEmpty(const sorted_list_ty *sorted_list)
{

	assert(NULL != sorted_list);
	assert(NULL != sorted_list->dlist);

	return DListIsEmpty(sorted_list->dlist);

}

sorted_list_iter_ty SortedListBegin(const sorted_list_ty *sorted_list)
{
	sorted_list_iter_ty sortedlist_begin_iter;

	assert(NULL != sorted_list);
	assert(NULL != sorted_list->dlist);

	sortedlist_begin_iter.internal_itr=DListBegin(sorted_list->dlist);

	return sortedlist_begin_iter;
}

sorted_list_iter_ty SortedListEnd(const sorted_list_ty *sorted_list)
{
	sorted_list_iter_ty sortedlist_end_iter;

	assert(NULL != sorted_list);
	assert(NULL != sorted_list->dlist);

	sortedlist_end_iter.internal_itr=DListEnd(sorted_list->dlist);

	return sortedlist_end_iter;
}

sorted_list_iter_ty SortedListNext(sorted_list_iter_ty iter)
{
	sorted_list_iter_ty sortedlist_next_iter;

	sortedlist_next_iter.internal_itr=DListNext(iter.internal_itr);

	return sortedlist_next_iter;
}

sorted_list_iter_ty SortedListPrev(sorted_list_iter_ty iter)
{
	sorted_list_iter_ty sortedlist_prev_iter;

	sortedlist_prev_iter.internal_itr = DListPrev(iter.internal_itr);

	return sortedlist_prev_iter;
}

void *SortedListGetData(sorted_list_iter_ty iter)
{

	return DListGetData(iter.internal_itr);
}

sorted_list_iter_ty SortedListInsert(sorted_list_ty *sorted_list, void *data)
{
    sorted_list_iter_ty iter;

    assert(NULL!=sorted_list);
    assert(NULL!=data);

    if(SortedListIsEmpty(sorted_list))
    {
        DListPushFront(sorted_list->dlist,data);

        return SortedListBegin(sorted_list);
    }

    iter = SortedListBegin(sorted_list);

    while(!SortedListIterIsEqual(iter, SortedListNext(SortedListEnd(sorted_list)))
        && 0 < sorted_list->compare_func(data,SortedListGetData(iter)))
    {
        iter = SortedListNext(iter);
    }

    iter.internal_itr = DListInsert(sorted_list->dlist,iter.internal_itr,data);

    return iter;
}

int SortedListIterIsEqual(sorted_list_iter_ty first_iter,sorted_list_iter_ty second_iter)
{
	return first_iter.internal_itr.dnode==second_iter.internal_itr.dnode;
	
}

sorted_list_iter_ty SortedListRemove(sorted_list_ty *sorted_list,sorted_list_iter_ty to_remove)
{
	sorted_list_iter_ty current_iter;

	assert(NULL != sorted_list);
	assert(NULL != to_remove.internal_itr.dnode);

	current_iter.internal_itr=DListRemove(sorted_list->dlist,to_remove.internal_itr);

	return current_iter;
}

sorted_list_iter_ty SortedListFind(const sorted_list_ty *sorted_list,sorted_list_iter_ty from,
												sorted_list_iter_ty to ,const void *element)
{
	sorted_list_iter_ty list_runner=from;

	assert(NULL != sorted_list);
	assert(NULL != from.internal_itr.dnode);
	assert(NULL != element);
	assert(NULL != to.internal_itr.dnode);
	assert(NULL != element);

	

	while(!SortedListIterIsEqual(list_runner,to) &&
								 0 == sorted_list->compare_func(SortedListGetData(list_runner),element))
	{
		list_runner=SortedListNext(list_runner);
	}

	return list_runner;

	
}

sorted_list_iter_ty SortedListFindIf(sorted_list_iter_ty from,sorted_list_iter_ty to ,cmp_func_ty cmp_func ,const void *param)
{	
	sorted_list_iter_ty list_runner=from;

	assert(NULL != from.internal_itr.dnode);
	assert(NULL != to.internal_itr.dnode);
	assert(NULL != param);
	assert(NULL != cmp_func);


	while(!SortedListIterIsEqual(list_runner,to) && 
								0 == cmp_func(SortedListGetData(list_runner),param))
	{
		list_runner=SortedListNext(list_runner);
	}

	return list_runner;
}

int SortedListForEach(sorted_list_iter_ty from, sorted_list_iter_ty to,op_func_ty op_func, void *func_param)
{
	sorted_list_iter_ty list_runner=from;
	int result = 0; 

	assert(NULL != from.internal_itr.dnode);
	assert(NULL != to.internal_itr.dnode);
	assert(NULL != func_param);
	assert(NULL != op_func);

	

	while (ISEQUAL != SortedListIterIsEqual(list_runner,to)) 
    {
        result = op_func(SortedListGetData(list_runner),func_param);

        if (ISEQUAL != result) 
        {
            return result;
        }

        list_runner=SortedListNext(list_runner);

    }
         

    return result; 
	
}

void SortedListMerge(sorted_list_ty *dest,sorted_list_ty *src)
{
	sorted_list_iter_ty src_iter;

	assert(NULL != src);
	assert(NULL != dest);

	
	src_iter = SortedListBegin(src);

	while(!SortedListIterIsEqual(src_iter,SortedListEnd(src)))
	{
		SortedListInsert(dest, SortedListGetData(src_iter));
		SortedListPopFront(src);
		src_iter = SortedListNext(src_iter);
	}
	SortedListInsert(dest, SortedListGetData(src_iter));
	SortedListPopFront(src);

}