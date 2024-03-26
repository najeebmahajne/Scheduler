/*******************************************************************************
Project: Doubly Linked List 
Name:Najeeb
Reviewer:Yan
Date:29.10.2023
Version: 1.0
*******************************************************************************/


#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <stddef.h> /*size_t*/

typedef enum {NO_ERROR, MALLOC_ERROR, GENERAL_ERR }dlist_status_ty;

typedef struct dlinkedlist dlist_ty;
typedef struct dnode dlist_node_ty;

typedef struct diter dlist_iter_ty;

struct diter
{
  dlist_node_ty *dnode;
};


/*
Function Description: Create a list.

Return value: Pointer to the list

Undefined behaviour:None

Time Complexity: O(1)

on failure: NULL.
*/
dlist_ty *DListCreate(void);

/*
Function Description: Destroy the list and free its resources.

Return value: void

Undefined behaviour: if pointer is NULL.

Time Complexity: O(n)

on failure: None.
*/
void DListDestroy(dlist_ty *dlist);

/*
Function Description: Inserts element to the start of the list

Return value: Status - 0 SUCCESS, 1 error

Undefined behaviour: if list or element is NULL.

Time Complexity: O(1)

on failure: Error code.
*/
dlist_status_ty DListPushFront(dlist_ty *dlist, void *element);

/*
Function Description: Inserts element to the end of the list

Return value: Status - 0 SUCCESS, 1 - memory allocation error

Undefined behaviour: if list or element is NULL.

Time Complexity: O(1)

on failure: Error code.
*/
dlist_status_ty DListPushBack(dlist_ty *dlist, void *element);

/*
Function Description: Removes the first element of the list

Return value: Status - 0 SUCCESS, 1 error

Undefined behaviour: if list is NULL

Time Complexity: O(1)

on failure: Error code.
*/
dlist_status_ty DListPopFront(dlist_ty *dlist);

/*
Function Description: Removes the last element of the list

Return value: Status - 0 SUCCESS, 1 error

Undefined behaviour: if list is NULL

Time Complexity: O(1)

on failure: Error code.
*/
dlist_status_ty DListPopBack(dlist_ty *dlist);

/*
Function Description: Count the number of elements in the list

Return value: Number of elements

Undefined behaviour: pointer is NULL;

Time Complexity: O(n)

on failure: None.
*/
size_t DListLength(const dlist_ty *dlist);

/*
Function Description: Check if list is empty

Return value: 1 - empty, 0 - not empty

Time Complexity: O(1)

on failure: None.

*/
int DListIsEmpty(const dlist_ty *dlist);

/*
Function Description: Find first element that is equal to element or NULL if not found

Return value: output dlist

Undefined behaviour: if list, is_match or element, output are NULL pointers.
Note:The function expects the is_match function to return 1 in case of success

Time Complexity: O(n)

on failure: Null.

*/
dlist_ty *DListMultiFind(const dlist_ty *dlist, int (*is_match)(const void *left,
					const void *right) ,const void *element, dlist_ty *output);

/*
Function Description: Head to list

Return value: head iterator

Undefined behaviour: if dlist_ty is NULL

Time Complexity: O(1)

on failure: None.
*/
dlist_iter_ty DListBegin(const dlist_ty *dlist);

/*
Function Description: Tail of the list

Return value: Tail iterator

Undefined behaviour: if dlist_ty is NULL

Time Complexity: O(1)

on failure: None.
*/
dlist_iter_ty DListEnd(const dlist_ty *dlist);

/*
Function Description: The next of after the iterator

Return value: the next iterator

Undefined behaviour: if dlist_iter_ty holds null address

Time Complexity: O(1)

on failure: None.
*/
dlist_iter_ty DListNext(dlist_iter_ty iter);

/*
Function Description: Find prev iterator

Return value: Pointer to prev iterator

Undefined behaviour: if dlist_iter_ty holds null address

Time Complexity: O(1)

on failure: None.
*/
dlist_iter_ty DListPrev(dlist_iter_ty iter);

/*
Function Description: Get data from a specific iterator in the list

Return value: Pointer to the data stored in the iterator

Undefined behaviour: if dlist_iter_ty holds null address

Time Complexity: O(1)

on failure: None.
*/
void *DListGetData(dlist_iter_ty iter);

/*
Function Description: Set data in a specific iterator in the list

Return value: void

Undefined behaviour: if dlist_iter_ty holds null address or data is NULL

Time Complexity: O(1)

on failure: None.
*/
void DListSetData(dlist_iter_ty iter, void *data);

/*
Function Description: Insert a new iterator with the specified data before a given iterator in the list

Return value: dlist_iter_ty

Undefined behaviour: if 'list' ,'data' is NULL or if where holds null address

Time Complexity: O(1)

on failure: NULL.

*/
dlist_iter_ty DListInsert(dlist_ty *dlist, dlist_iter_ty where, void *data);

/*
Function Description: Remove a specific iterator from the list

Return value: dlist_iter_ty

Undefined behaviour: if 'list' is NULL or 'to_remove' holds null address

Time Complexity: O(1)

on failure: NULL.

*/
dlist_iter_ty DListRemove(dlist_ty *dlist, dlist_iter_ty to_remove);


/*
Function Description: Apply a given action to a range of iterators in the list

Return value: same error codes as the ones returned by action

Undefined behaviour: If 'list', 'from', 'to', or 'Action' is NULL.
Note: We expect the action to return 0 for success and non zero for failures.

Time Complexity: O(n)

on failure: Error code.

*/
int DListForEach(dlist_ty *dlist, dlist_iter_ty from, dlist_iter_ty to,
				int (*action)(void *data, void *param), void *param);

/*
Function Description: cut out a from iterator 'to' to iterator 'where' from a list
    to specified point (where). 

Unspecified behavior: from, to, where holding null addresses.
Return value: void

Time Complexity: O(1)

on failure: None.

*/
void DListSplice(dlist_iter_ty from, dlist_iter_ty to, dlist_iter_ty where);


int DListIterIsEqual(dlist_iter_ty first_iter, dlist_iter_ty second_iter);


void PrintDLinkedList(dlist_ty* dlist);

#endif /*__DOUBLY_LINKED_LIST_H__*/
