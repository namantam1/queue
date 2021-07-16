/* 
MIT License

Copyright (c) 2021 Naman Tamrakar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

IDEA:
Queue work on principle of FIFO
i.e. first in first out

So the idea here is to use a linked list
for creating a queue for dynamic size handling.

STRATEGY :-
=========
ADD:        add an element to the tail of linked list and point tail to it.
DEQUEUE:    remove the element from the head and point head next to it.
*/

#include "queue.h"
#include <stdio.h>
#include <string.h>

// Linked list node definitions
typedef struct Node
{
    void *data;
    struct Node *next;
} node;
typedef node *node_ptr;
typedef const node *c_node_ptr;

// NODE IMPLEMENTATION
static void _copy_generic_data(void_ptr *target, c_void_ptr data, size_t size)
{
    *target = malloc(size);

    if (!target)
    {
        printf("StackOverflow line:29 Exit(0)!\n");
        exit(0);
    }
    // printf("data: %u\n", *target);
    memcpy(*target, data, size);
}

static node_ptr _create_node(c_void_ptr data, node_ptr next, size_t size)
{
    // printf("create node\n");
    node_ptr new = (node_ptr)malloc(sizeof(node));

    if (!new)
    {
        printf("StackOverflow line:41 Exit(0)!\n");
        exit(0);
    }

    _copy_generic_data(&(new->data), data, size);
    new->next = next;
    return new;
}

static void _destroy_node(node_ptr *n)
{
    // printf("destroy node\n");
    free((*n)->data);
    free(*n);
    n = NULL;
}

// ##################################################################################
//  QUEUE IMPLEMENTATION                                                            #
// ##################################################################################

typedef struct Queue
{
    node_ptr head;
    node_ptr tail;
    int length;
    size_t size;
} queue;

/**
 * Create a new queue from givin data.
 * 
 * @param size: Size of generic data
 * @param data: Generic data (option)
 * 
 * @returns queue pointer
*/
queue_ptr create_queue(size_t size, c_void_ptr data)
{
    // printf("create queue\n");

    // allocated the memory to queue pointer
    queue_ptr q = (queue_ptr)malloc(sizeof(queue));
    q->size = size;

    node *head = NULL;
    int length = 0;

    // if data is passed the copy the data to new
    // memory and point the head to it.
    if (data)
    {
        head = _create_node(data, NULL, q->size);
        length = 1;
    }

    q->head = q->tail = head;
    q->length = length;

    return q;
}

/**
 * Function to add the element to to queue
 * 
 * @param q: queue pointer
 * @param data: data to add to queue
 * @return void(0)
*/
void add(queue_ptr q, c_void_ptr data)
{
    // creating a new node from givin data
    node_ptr new = _create_node(data, NULL, q->size);

    // if tail is present
    if (q->tail)
    {
        // 1. create a new node with next null
        // 2. point tail next to new node
        q->tail->next = new;
        // 3. point tail to new node
        q->tail = new;

        q->length += 1;
    }
    // else point head and tail both to new node
    else
    {
        q->head = q->tail = new;
        q->length = 1;
    }
}

/**
 * Function to remove a node from queue from top
 * 
 * @param q: queue pointer
 * @param data: a mutable data pointer with memory allocated
 * or use static varible pointer.
 * @return void(0)
*/
bool dequeue(queue_ptr q, void_ptr data)
{
    // check for empty
    if (!q->head)
    {
        printf("queue is empty\n");
        return false;
    }
    else
    {
        // copy the memory if pointer allocated memory
        if (data)
            memcpy(data, q->head->data, q->size);

        // point temp pointer to head
        node_ptr temp = q->head;

        // point to next head
        q->head = q->head->next;

        // delete the temp node pointer memory
        _destroy_node(&temp);

        // decrease length
        q->length -= 1;

        return true;
    }
}

/**
 * Function to get top node data of the queue
 * @param q: queue pointer
 * @return data pointer if queue not empty else NULL
*/
void *peek(queue_ptr q)
{
    return q->head ? q->head->data : q->head;
}

/**
 * Print the string representation of queue
 * 
 * @param q: queue pointer
 * @param print: print function with a data pointer argument
 * @return void(0)
*/
void print_queue(
    queue_ptr q,
    void (*print)(void_ptr))
{
    if (q == NULL)
    {
        printf("queue pointer is NULL, %p\n", q);
        return;
    }

    // get the head pointer
    node_ptr head = q->head;

    printf("[");
    while (head)
    {
        print(head->data);
        head = head->next;
        if (head)
            printf(", ");
    }
    printf("]\n");
}

/**
 * Function to get the current length of queue
 * 
 * @param q: queue pointer
 * @return length(int)
*/
int length(queue_ptr q)
{
    return q->length;
}

/**
 * Function to check if queue is empty
 * 
 * @param q: queue pointer
 * @return boolean
*/
bool is_empty(queue_ptr q)
{
    return q->head ? false : true;
}

/**
 * Function to clear all the memory created along with queue
 * 
 * @param q: queue double pointer
*/
void destroy_queue(queue_ptr *q)
{
    // iterate until head is present
    while ((*q)->head)
    {
        dequeue(*q, NULL);
    }
    free(*q);
    *q = NULL;
}
