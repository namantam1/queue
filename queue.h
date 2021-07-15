#include <stdlib.h>
#include <stdbool.h>

#ifndef __QUEUE_H__
#define __QUEUE_H__

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void *void_ptr;
    typedef const void *c_void_ptr;

    typedef struct Queue queue;
    typedef queue *queue_ptr;

    /**
     * Create a new queue from givin data.
     * 
     * @param size: Size of generic data
     * @param data: Generic data (option)
     * 
     * @returns queue pointer
    */
    queue *create_queue(size_t, const void *);

    /**
     * Function to add the element to to queue
     * 
     * @param q: queue pointer
     * @param data: data to add to queue
     * @return void(0)
    */
    void add(queue *, const void *);

    /**
     * Function to remove a node from queue from top
     * 
     * @param q: queue pointer
     * @param data: a mutable data pointer with memory allocated
     * or use static varible pointer.
     * @return void(0)
    */
    void dequeue(queue *, void *);

    /**
     * Function to get top node data of the queue
     * @param q: queue pointer
     * @return data pointer if queue not empty else NULL
    */
    void *peek(queue *);

    /**
     * Print the string representation of queue
     * 
     * @param q: queue pointer
     * @param print: print funtion with a data pointer argument
     * @return void(0)
    */
    void print_queue(queue *, void (*)(void *));

    /**
     * Function to get the current length of queue
     * 
     * @param q: queue pointer
     * @return length(int)
    */
    int length(queue *);

    /**
     * Function to clear all the memory created along with queue
     * 
     * @param q: queue pointer
    */
    void destroy_queue(queue *);

    /**
     * Function to check if queue is empty
     * 
     * @param q: queue pointer
     * @return boolean
    */
    bool is_empty(queue *);

#ifdef __cplusplus
}
#endif

#endif // __QUEUE_H__