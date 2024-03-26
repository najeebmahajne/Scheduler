#include <stdlib.h>/*malloc , free*/
#include <assert.h>/*assert*/
#include <stdio.h>/*fprintf*/

#include "doublylinkedlist.h"/*my header*/


struct dnode
{
	void *data;
	struct dnode *next;
	struct dnode *prev;
};

struct dlinkedlist 
{
	dlist_node_ty *head;
	dlist_node_ty *tail;
};

dlist_ty *DListCreate(void)
{
	dlist_ty *dlist=NULL;

	dlist = (dlist_ty *)malloc(sizeof(dlist_ty));

	if(NULL == dlist)
	{
		fprintf(stderr,"%s","Memory Allocation Error!");
		return NULL;
	}

	dlist->head=NULL;
	dlist->head=(dlist_node_ty *)malloc(sizeof(dlist_node_ty));

	if (NULL==dlist->head)
	{
		fprintf(stderr, "%s\n","MEMORY ALLOCATION!\n");
		return NULL;
	}

	dlist->head->data=NULL;
	dlist->head->next=NULL;
	dlist->head->prev=NULL;

	dlist->tail=(dlist_node_ty *)malloc(sizeof(dlist_node_ty));

	if (NULL==dlist->tail)
	{
		fprintf(stderr, "%s\n","MEMORY ALLOCATION!\n");
		return NULL;
	}


	dlist->tail->data=NULL;
	dlist->tail->next=NULL;

	dlist->tail->prev=dlist->head;

	dlist->head->next=dlist->tail;

	return dlist;
}

void DListDestroy(dlist_ty *dlist)
{
	assert(NULL != dlist);

	while(!DListIsEmpty(dlist))
	{
		DListPopFront(dlist);
	}

	free(dlist->head);
	dlist->head=NULL;
	free(dlist->tail);
	dlist->tail=NULL;
	free(dlist);
	dlist = NULL;
}

dlist_status_ty DListPushFront(dlist_ty *dlist, void *element)
{
	dlist_node_ty *new_node=NULL;


	assert(NULL!=dlist);
	assert(NULL!=element);

	new_node=(dlist_node_ty *)malloc(sizeof(dlist_node_ty)); 

	if(NULL==new_node)
	{
		fprintf(stderr, "%s\n","MEMORY ALLOCATION!\n");
		return MALLOC_ERROR;
	}

	new_node->data=NULL;
	new_node->prev=NULL;

	dlist->head->data = element;
	dlist->head->prev = new_node;
	new_node->next = dlist->head;
	dlist->head = new_node;


	return NO_ERROR; 
}

dlist_status_ty DListPushBack(dlist_ty *dlist, void *element)
{

    dlist_node_ty *new_node=NULL;

    assert(NULL!=dlist);
    assert(NULL!=element);

    new_node=(dlist_node_ty *)malloc(sizeof(dlist_node_ty)); 

    if(NULL==new_node)
    {
        fprintf(stderr, "%s\n","MEMORY ALLOCATION!\n");
        return MALLOC_ERROR;
    }

    new_node->data=NULL;
    new_node->next=NULL;

    new_node->prev=dlist->tail;
    dlist->tail->data=element;
    dlist->tail->next=new_node;
    dlist->tail=new_node;

    return NO_ERROR;
}

dlist_status_ty DListPopFront(dlist_ty *dlist)
{
	dlist_node_ty *prev_head=NULL;

	assert(NULL != dlist);

	if(!DListIsEmpty(dlist))
	{
		dlist->head = dlist->head->next;
		dlist->head->data = NULL;
		prev_head=dlist->head->prev;
		dlist->head->prev = NULL;

		free(prev_head);
		prev_head=NULL;
	}

	return NO_ERROR; 
}

dlist_status_ty DListPopBack(dlist_ty *dlist)
{
	dlist_node_ty *current=NULL;

	assert(NULL != dlist);

	current = dlist->tail;

	if(!DListIsEmpty(dlist))
	{
		current = dlist->tail;
		current->prev->data = NULL;

		current->prev->next = NULL;
		dlist->tail = current->prev;
		free(current);
	}

	return NO_ERROR; 
}

size_t DListLength(const dlist_ty *dlist)

{

    size_t count = 0;
    dlist_node_ty *current =NULL;
    
    assert(NULL != dlist);

    current = dlist->head->next;

    while (NULL != current->data) 
    {
        ++count;
        current = current->next;
    }

    return count;
}


int DListIsEmpty(const dlist_ty *dlist)
{
	assert(NULL != dlist);

	return dlist->head->next==dlist->tail;
}

dlist_ty *DListMultiFind(const dlist_ty *dlist,int (*is_match)(const void *left,
					const void *right) ,const void *element, dlist_ty *output)
{
    dlist_node_ty *current = NULL;

    assert(NULL != dlist);
    assert(NULL != output);
    assert(NULL != element);
    assert(NULL != is_match);
    

    current = dlist->head->next;

    while (NULL != current->data) 
    {
        if (1 == is_match(current->data, element)) 
        {
            DListPushBack(output, current->data);
        }
        current = current->next;
    }

    return output;
}



dlist_iter_ty DListBegin(const dlist_ty *dlist)
{
	dlist_iter_ty dlist_begin_iter;

	assert(NULL != dlist);

    dlist_begin_iter.dnode = dlist->head->next;

    return dlist_begin_iter;
}

dlist_iter_ty DListEnd(const dlist_ty *dlist)
{
	dlist_iter_ty dlist_end_iter;

	assert(NULL != dlist);

	dlist_end_iter.dnode = dlist->tail->prev;

	return dlist_end_iter;
}

dlist_iter_ty DListNext(dlist_iter_ty iter)
{
	dlist_iter_ty dlist_next_iter;

	assert(NULL != iter.dnode);

	dlist_next_iter.dnode =iter.dnode->next;

	return dlist_next_iter;
}

dlist_iter_ty DListPrev(dlist_iter_ty iter)
{
	dlist_iter_ty dlist_prev_iter;

	assert(NULL != iter.dnode);

	dlist_prev_iter.dnode =iter.dnode->prev;

	return dlist_prev_iter;
}

void *DListGetData(dlist_iter_ty iter)
{
	assert(NULL != iter.dnode);

	return iter.dnode->data;
}

void DListSetData(dlist_iter_ty iter, void *data)
{
	assert(NULL != iter.dnode);
    assert(NULL != data);

	iter.dnode->data=data;
}

dlist_iter_ty DListInsert(dlist_ty *dlist, dlist_iter_ty where, void *data) 
{
    dlist_node_ty *new_node =NULL;
    dlist_iter_ty new_iter;

    assert(NULL != dlist);
    assert(NULL != data);
    assert(NULL != where.dnode);

    new_node = (dlist_node_ty *)malloc(sizeof(dlist_node_ty));
    if (NULL == new_node) 
    {
        return where;
    }

    new_node->data = data;
    new_node->next = where.dnode;
    new_node->prev = where.dnode->prev;
    where.dnode->prev->next = new_node;
    where.dnode->prev = new_node;

    new_iter.dnode = new_node;
    return new_iter;
}

dlist_iter_ty DListRemove(dlist_ty *dlist, dlist_iter_ty to_remove) 
{

    dlist_node_ty *node_to_remove = NULL;
    dlist_iter_ty next_iter;
    dlist_node_ty *previous_node = NULL;
    dlist_node_ty *next_node = NULL;

    assert(NULL != dlist);
    assert(NULL !=to_remove.dnode);

    node_to_remove = to_remove.dnode;
	previous_node = node_to_remove->prev;
	next_node = node_to_remove->next;


    if (NULL != previous_node) 
    {
        previous_node->next = next_node;
    }
    if (NULL != next_node) 
    {
        next_node->prev = previous_node;
    }

   
    next_iter.dnode = next_node;

    free(node_to_remove);

    return next_iter;
}

int DListForEach(dlist_ty *dlist, dlist_iter_ty from, dlist_iter_ty to,
                 int (*action)(void *data, void *param), void *param) 
{
    

    dlist_node_ty *current = NULL;
    int result = 0; 

    assert(NULL != dlist);
    assert(NULL != from.dnode);
	assert(NULL != to.dnode);
    assert(NULL != action);

    if(DListIsEmpty(dlist))
    {
    	return 0;
    }

    current = from.dnode;
    while ((current != to.dnode->next)) 
    {
        result = action(current->data,param);

        if (1 != result) 
        {
            return result;
        }

        current = current->next;

    }
    

    return result; 
}

void DListSplice(dlist_iter_ty from, dlist_iter_ty to, dlist_iter_ty where) 
{

	dlist_node_ty *from_node =NULL;
    dlist_node_ty *to_node = NULL;
    dlist_node_ty *where_node = NULL;

	assert(NULL != from.dnode);
	assert(NULL != to.dnode);
	assert(NULL != where.dnode);

    from_node = from.dnode;
    to_node = to.dnode;
    where_node = where.dnode;

    from_node->prev->next = to_node->next;
    to_node->next->prev = from_node->prev;

    where_node->prev->next = from_node;
    from_node->prev = where_node->prev;

    to_node->next = where_node;
    where_node->prev = to_node;
}



void PrintDLinkedList(dlist_ty *dlist)
{
	dlist_node_ty *tmp_node=NULL;

	assert(NULL != dlist);

	if(NULL == dlist)
	{   
		printf("EMPTY!!\n");
		return;
	}

	tmp_node = dlist->head;

	while(tmp_node->next != dlist->tail)
	{
		tmp_node = tmp_node->next;
		printf("%d\n",*(int *)tmp_node->data);
		
	}


}

struct dnode *ReturnDNode(dlist_iter_ty iter)
{
	return iter.dnode;
}

int DListIterIsEqual(dlist_iter_ty first_iter, dlist_iter_ty second_iter)
{
    return first_iter.dnode == second_iter.dnode;
}